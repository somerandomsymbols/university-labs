using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Etap12;
using Microsoft.AspNetCore.Authorization;

namespace Etap12.Controllers
{
    public class PatientsController : Controller
    {
        private readonly ISTP1Context _context;

        public PatientsController(ISTP1Context context)
        {
            _context = context;
        }

        // GET: Patients
        public async Task<IActionResult> Index(int? id, string? name)
        {
            ViewBag.DoctorId = id;

            if (id == null)
                //return RedirectToAction("Doctors", "Index");
                return View(await _context.Patients.Include(p => p.Doctor).ToListAsync());

            ViewBag.DoctorName = _context.Doctors.FirstOrDefault(d => d.DoctorId == id).DoctorName;
            var iSTP1Context = _context.Patients.Where(p => p.DoctorId == id).Include(p => p.Doctor);
            return View(await iSTP1Context.ToListAsync());
        }

        /*public async Task<IActionResult> IndexGlobal()
        {
            return View(await _context.Patients.Include(p => p.Doctor).ToListAsync());
        }*/

        // GET: Patients/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var patient = await _context.Patients
                .Include(p => p.Doctor)
                .FirstOrDefaultAsync(m => m.PatientId == id);
            if (patient == null)
            {
                return NotFound();
            }

            return View(patient);
        }

        // GET: Patients/Insurances/5
        public async Task<IActionResult> Insurances(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var patient = await _context.Patients
                .Include(p => p.Doctor)
                .FirstOrDefaultAsync(m => m.PatientId == id);
            if (patient == null)
            {
                return NotFound();
            }

            //return View(patient);
            return RedirectToAction("Index", "Insurances", new { id = patient.PatientId, name = patient.PatientName });
        }

        // GET: Patients/Create
        [Authorize(Roles = "admin")]
        public IActionResult Create(int doctorId)
        {
            //ViewData["DoctorId"] = new SelectList(_context.Doctors, "DoctorId", "DateStartWork");
            ViewBag.DoctorId = doctorId;
            ViewBag.DoctorName = _context.Doctors.Where(d => d.DoctorId == doctorId).FirstOrDefault().DoctorName;
            return View();
        }

        // POST: Patients/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Create(int doctorId, [Bind("PatientId,PatientName,DateOfBirth,HomeAdress,PatientPhoneNumber,Height,Weight,Passport,DoctorId")] Patient patient)
        {
            if (ModelState.IsValid)
            {
                _context.Add(patient);
                await _context.SaveChangesAsync();
                //return RedirectToAction(nameof(Index));
            }
            //ViewData["DoctorId"] = new SelectList(_context.Doctors, "DoctorId", "DateStartWork", patient.DoctorId);
            //return View(patient);
            return RedirectToAction("Index", "Patients", new { id = doctorId, name = _context.Doctors.Where(d => d.DoctorId == doctorId).FirstOrDefault().DoctorName });
        }

        // GET: Patients/Edit/5
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var patient = await _context.Patients.FindAsync(id);

            if (patient == null)
            {
                return NotFound();
            }

            ViewBag.Doctors = _context.Doctors.ToList();
            ViewData["DoctorId"] = new SelectList(_context.Doctors, "DoctorId", "DateStartWork", patient.DoctorId);
            return View(patient);
        }

        // POST: Patients/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Edit(int id, [Bind("PatientId,PatientName,DateOfBirth,HomeAdress,PatientPhoneNumber,Height,Weight,Passport,DoctorId")] Patient patient)
        {
            if (id != patient.PatientId)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(patient);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!PatientExists(patient.PatientId))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            ViewData["DoctorId"] = new SelectList(_context.Doctors, "DoctorId", "DateStartWork", patient.DoctorId);
            return View(patient);
        }

        // GET: Patients/Delete/5
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var patient = await _context.Patients
                .Include(p => p.Doctor)
                .FirstOrDefaultAsync(m => m.PatientId == id);
            if (patient == null)
            {
                return NotFound();
            }

            return View(patient);
        }

        // POST: Patients/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var patient = await _context.Patients.FindAsync(id);
            _context.Patients.Remove(patient);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool PatientExists(int id)
        {
            return _context.Patients.Any(e => e.PatientId == id);
        }
    }
}
