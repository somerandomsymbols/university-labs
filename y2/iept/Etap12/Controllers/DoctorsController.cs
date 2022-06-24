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
    public class DoctorsController : Controller
    {
        private readonly ISTP1Context _context;

        public DoctorsController(ISTP1Context context)
        {
            _context = context;
        }

        // GET: Doctors
        public async Task<IActionResult> Index(int? id, string? name)
        {
            ViewBag.HospitalId = id;

            if (id == null)
                //return RedirectToAction("Hospitals", "Index");
                return View(await _context.Doctors.Include(d => d.Hospital).ToListAsync());

            ViewBag.HospitalName = _context.Hospitals.FirstOrDefault(h => h.HospitalId == id).HospitalName;
            var iSTP1Context = _context.Doctors.Where( d => d.HospitalId == id).Include(d => d.Hospital);
            return View(await iSTP1Context.ToListAsync());
        }

        /*public async Task<IActionResult> IndexGlobal()
        {
            return View(await _context.Doctors.Include(d => d.Hospital).ToListAsync());
        }*/

        // GET: Doctors/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var doctor = await _context.Doctors
                .Include(d => d.Hospital)
                .FirstOrDefaultAsync(m => m.DoctorId == id);
            if (doctor == null)
            {
                return NotFound();
            }

            return View(doctor);
        }

        // GET: Doctors/Patients/5
        public async Task<IActionResult> Patients(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var doctor = await _context.Doctors
                .Include(d => d.Hospital)
                .FirstOrDefaultAsync(m => m.DoctorId == id);
            if (doctor == null)
            {
                return NotFound();
            }

            //return View(doctor);
            return RedirectToAction("Index", "Patients", new { id = doctor.DoctorId, name = doctor.DoctorName });
        }

        // GET: Doctors/Create
        [Authorize(Roles = "admin")]
        public IActionResult Create(int hospitalId)
        {
            //ViewData["HospitalId"] = new SelectList(_context.Hospitals, "HospitalId", "HospitalAdress");
            ViewBag.HospitalId = hospitalId;
            ViewBag.HospitalName = _context.Hospitals.Where(h => h.HospitalId == hospitalId).FirstOrDefault().HospitalName;
            return View();
        }

        // POST: Doctors/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Create(int hospitalId, [Bind("DoctorId,DoctorName,Education,DateStartWork,DoctorPhoneNumber,DoctorPhoto,HospitalId")] Doctor doctor)
        {
            if (ModelState.IsValid)
            {
                _context.Add(doctor);
                await _context.SaveChangesAsync();
                //return RedirectToAction(nameof(Index));
                
            }
            //ViewData["HospitalId"] = new SelectList(_context.Hospitals, "HospitalId", "HospitalAdress", doctor.HospitalId);
            //return View(doctor);

            return RedirectToAction("Index", "Doctors", new { id = hospitalId, name = _context.Hospitals.Where(h => h.HospitalId == hospitalId).FirstOrDefault().HospitalName });
        }

        // GET: Doctors/Edit/5
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var doctor = await _context.Doctors.FindAsync(id);
            if (doctor == null)
            {
                return NotFound();
            }

            ViewBag.Hospitals = _context.Hospitals.ToList();
            ViewData["HospitalId"] = new SelectList(_context.Hospitals, "HospitalId", "HospitalAdress", doctor.HospitalId);
            return View(doctor);
        }

        // POST: Doctors/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Edit(int id, [Bind("DoctorId,DoctorName,Education,DateStartWork,DoctorPhoneNumber,DoctorPhoto,HospitalId")] Doctor doctor)
        {
            if (id != doctor.DoctorId)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(doctor);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!DoctorExists(doctor.DoctorId))
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
            ViewData["HospitalId"] = new SelectList(_context.Hospitals, "HospitalId", "HospitalAdress", doctor.HospitalId);
            return View(doctor);
        }

        // GET: Doctors/Delete/5
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var doctor = await _context.Doctors
                .Include(d => d.Hospital)
                .FirstOrDefaultAsync(m => m.DoctorId == id);
            if (doctor == null)
            {
                return NotFound();
            }

            return View(doctor);
        }

        // POST: Doctors/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var doctor = await _context.Doctors.FindAsync(id);
            _context.Doctors.Remove(doctor);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool DoctorExists(int id)
        {
            return _context.Doctors.Any(e => e.DoctorId == id);
        }
    }
}
