using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Etap12.Controllers
{
    [Route("api/Hospitals")]
    [ApiController]
    public class HospitalsApiController : ControllerBase
    {
        private readonly ISTP1Context _context;

        public HospitalsApiController(ISTP1Context context)
        {
            _context = context;
        }

        // GET: api/Hospitals
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Object>>> GetHospitals()
        {
            return await _context.Hospitals
                .Select(h => new { h.HospitalId, h.HospitalName, h.HospitalAdress, h.HospitalPhoneNumber, h.HospitalPhoto, doctorsCount = h.Doctors.Count})
                .ToListAsync();
        }

        // GET: api/Hospitals/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Object>> GetHospital(int id)
        {
            var hospital = await _context.Hospitals.FindAsync(id);

            if (hospital == null)
            {
                return NotFound();
            }

            var dlist = await _context.Doctors
                .Where(d => d.HospitalId == id)
                .Select(d => new { d.DoctorId, d.DoctorName })
                .ToListAsync();

            return new { hospital.HospitalId, hospital.HospitalName, hospital.HospitalAdress, hospital.HospitalPhoneNumber, hospital.HospitalPhoto, doctors = dlist };
        }

        // GET: api/Patients/5
        [Route("filter")]
        [HttpGet("{term}/{callback}")]
        public async Task<ActionResult<Object>> FilterHospitals(int id, [FromQuery] string term, [FromQuery] string callback)
        {
            if (term == null)
                term = "";
            term = term.ToLower();
            var hospitals = await _context.Hospitals.Where(h => h.HospitalName.ToLower().StartsWith(term)).Select(d => new { id = d.HospitalId, label = d.HospitalName, value = d.HospitalName }).ToListAsync();
            string response = "([";

            foreach (var h in hospitals)
            {
                response = response + "{ " + String.Format("\"id\":\"{0}\", \"label\":\"{1}\", \"value\":\"{2}\"", h.id, h.label, h.value) + " },";
            }

            response = callback + response.Substring(0, response.Length - 1) + "])";
            return response;
        }

        // PUT: api/Hospitals/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPut("{id}")]
        public async Task<IActionResult> PutHospital(int id, Hospital hospital)
        {
            if (id != hospital.HospitalId)
            {
                return BadRequest();
            }

            _context.Entry(hospital).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!HospitalExists(id))
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

        // POST: api/Hospitals
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPost]
        public async Task<ActionResult<Object>> PostHospital(Hospital hospital)
        {
            _context.Hospitals.Add(hospital);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetHospital", new { id = hospital.HospitalId }, new { hospital.HospitalId, hospital.HospitalName, hospital.HospitalAdress, hospital.HospitalPhoneNumber, hospital.HospitalPhoto });
        }

        // DELETE: api/Hospitals/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<Hospital>> DeleteHospital(int id)
        {
            var hospital = await _context.Hospitals.FindAsync(id);

            if (hospital == null)
            {
                return NotFound();
            }

            _context.Hospitals.Remove(hospital);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool HospitalExists(int id)
        {
            return _context.Hospitals.Any(e => e.HospitalId == id);
        }
    }
}
