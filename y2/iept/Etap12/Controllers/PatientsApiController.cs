using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Etap12.Controllers
{
    [Route("api/Patients")]
    [ApiController]
    public class PatientsApiController : ControllerBase
    {
        private readonly ISTP1Context _context;

        public PatientsApiController(ISTP1Context context)
        {
            _context = context;
        }

        // GET: api/Patients
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Object>>> GetPatients()
        {
            return await _context.Patients
                .Select(p => new { p.PatientId, p.PatientName, p.PatientPhoneNumber, p.HomeAdress, p.DateOfBirth, p.Height, p.Weight, p.Passport, p.DoctorId, insurancesCount = p.Insurances.Count })
                .ToListAsync();
        }

        // GET: api/Patients/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Object>> GetPatient(int id)
        {
            var patient = await _context.Patients.FindAsync(id);

            if (patient == null)
            {
                return NotFound();
            }

            var ilist = await _context.Insurances
                .Where(i => i.PatientId == id)
                .Select(i => new { i.InsuranceId, i.Balance, i.InsuranceCases })
                .ToListAsync();

            return new { patient.PatientId, patient.PatientName, patient.PatientPhoneNumber, patient.HomeAdress, patient.DateOfBirth, patient.Height, patient.Weight, patient.Passport, patient.DoctorId, insurances = ilist };
        }

        // GET: api/Patients/5
        [Route("filter")]
        [HttpGet("{term}/{callback}")]
        public async Task<ActionResult<Object>> FilterPatients(int id, [FromQuery] string term, [FromQuery] string callback)
        {
            if (term == null)
                term = "";
            term = term.ToLower();
            var patients = await _context.Patients.Where(p => p.PatientName.ToLower().StartsWith(term)).Select(p => new { id = p.PatientId, label = p.PatientName, value = p.PatientName }).ToListAsync();
            string response = "([";

            foreach (var p in patients)
            {
                response = response + "{ " + String.Format("\"id\":\"{0}\", \"label\":\"{1}\", \"value\":\"{2}\"", p.id, p.label, p.value) + " },";
            }

            response = callback + response.Substring(0, response.Length - 1) + "])";
            return response;
        }

        // PUT: api/Patients/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPut("{id}")]
        public async Task<IActionResult> PutPatient(int id, Patient patient)
        {
            if (id != patient.PatientId)
            {
                return BadRequest();
            }

            _context.Entry(patient).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!PatientExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        // POST: api/Patients
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPost]
        public async Task<ActionResult<Object>> PostPatient(Patient patient)
        {
            _context.Patients.Add(patient);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetPatient", new { id = patient.PatientId }, new { patient.PatientId, patient.PatientName, patient.PatientPhoneNumber, patient.HomeAdress, patient.DateOfBirth, patient.Height, patient.Weight, patient.Passport, patient.DoctorId });
        }

        // DELETE: api/Patients/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<Patient>> DeletePatient(int id)
        {
            var patient = await _context.Patients.FindAsync(id);

            if (patient == null)
            {
                return NotFound();
            }

            _context.Patients.Remove(patient);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool PatientExists(int id)
        {
            return _context.Patients.Any(e => e.PatientId == id);
        }
    }
}
