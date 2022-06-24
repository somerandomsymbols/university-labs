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
    public class InsurancesController : Controller
    {
        private readonly ISTP1Context _context;

        public InsurancesController(ISTP1Context context)
        {
            _context = context;
        }

        // GET: Insurances
        public async Task<IActionResult> Index(int? id, string name)
        {
            ViewBag.PatientId = id;

            if (id == null)
                //return RedirectToAction("Patients", "Index");
                return View(await _context.Insurances.Include(i => i.Patient).ToListAsync());

            ViewBag.PatientName = _context.Patients.FirstOrDefault(p => p.PatientId == id).PatientName;
            var iSTP1Context = _context.Insurances.Where(i => i.PatientId == id).Include(i => i.Patient);
            return View(await iSTP1Context.ToListAsync());
        }

        /*public async Task<IActionResult> IndexGlobal()
        {
            return View(await _context.Insurances.Include(i => i.Patient).ToListAsync());
        }*/

        // GET: Insurances/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var insurance = await _context.Insurances
                .Include(i => i.Patient)
                .FirstOrDefaultAsync(m => m.InsuranceId == id);
            if (insurance == null)
            {
                return NotFound();
            }

            return View(insurance);
        }

        // GET: Insurances/Create
        public IActionResult Create(int patientId)
        {
            //ViewData["PatientId"] = new SelectList(_context.Patients, "PatientId", "DateOfBirth");
            ViewBag.PatientId = patientId;
            ViewBag.PatientName = _context.Patients.Where(d => d.PatientId == patientId).FirstOrDefault().PatientName;
            return View();
        }

        // POST: Insurances/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Create(int patientId, [Bind("InsuranceId,PatientId,Balance,InsuranceCases")] Insurance insurance)
        {
            if (ModelState.IsValid)
            {
                _context.Add(insurance);
                await _context.SaveChangesAsync();
                //return RedirectToAction(nameof(Index));
            }
            //ViewData["PatientId"] = new SelectList(_context.Patients, "PatientId", "DateOfBirth", insurance.PatientId);
            //return View(insurance);
            return RedirectToAction("Index", "Insurances", new { id = patientId, name = _context.Patients.Where(p => p.PatientId == patientId).FirstOrDefault().PatientName });
        }

        // GET: Insurances/Edit/5
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var insurance = await _context.Insurances.FindAsync(id);
            if (insurance == null)
            {
                return NotFound();
            }

            ViewBag.Patients = _context.Patients.ToList();
            ViewData["PatientId"] = new SelectList(_context.Patients, "PatientId", "DateOfBirth", insurance.PatientId);
            return View(insurance);
        }

        // POST: Insurances/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Edit(int id, [Bind("InsuranceId,PatientId,Balance,InsuranceCases")] Insurance insurance)
        {
            if (id != insurance.InsuranceId)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(insurance);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!InsuranceExists(insurance.InsuranceId))
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
            ViewData["PatientId"] = new SelectList(_context.Patients, "PatientId", "DateOfBirth", insurance.PatientId);
            return View(insurance);
        }

        // GET: Insurances/Delete/5
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var insurance = await _context.Insurances
                .Include(i => i.Patient)
                .FirstOrDefaultAsync(m => m.InsuranceId == id);
            if (insurance == null)
            {
                return NotFound();
            }

            return View(insurance);
        }

        // POST: Insurances/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var insurance = await _context.Insurances.FindAsync(id);
            _context.Insurances.Remove(insurance);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool InsuranceExists(int id)
        {
            return _context.Insurances.Any(e => e.InsuranceId == id);
        }
    }
}
