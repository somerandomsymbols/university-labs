using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Etap12;
using Microsoft.AspNetCore.Http;
using System.IO;
using ClosedXML.Excel;
using Microsoft.AspNetCore.Authorization;

namespace Etap12.Controllers
{
    public class HospitalsController : Controller
    {
        private readonly ISTP1Context _context;

        public HospitalsController(ISTP1Context context)
        {
            _context = context;
        }

        // GET: Hospitals
        public async Task<IActionResult> Index()
        {
            return View(await _context.Hospitals.ToListAsync());
        }

        // GET: Hospitals/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var hospital = await _context.Hospitals
                .FirstOrDefaultAsync(m => m.HospitalId == id);
            if (hospital == null)
            {
                return NotFound();
            }

            return View(hospital);
        }

        // GET: Hospitals/Doctors/5
        public async Task<IActionResult> Doctors(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var hospital = await _context.Hospitals
                .FirstOrDefaultAsync(m => m.HospitalId == id);
            if (hospital == null)
            {
                return NotFound();
            }

            //return View(hospital);
            return RedirectToAction("Index", "Doctors", new { id = hospital.HospitalId, name = hospital.HospitalName });
        }

        // GET: Hospitals/Create
        [Authorize(Roles = "admin")]
        public IActionResult Create()
        {
            return View();
        }

        // POST: Hospitals/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Create([Bind("HospitalId,HospitalName,HospitalPhoneNumber,HospitalAdress,HospitalPhoto")] Hospital hospital)
        {
            if (ModelState.IsValid)
            {
                _context.Add(hospital);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(hospital);
        }


        // GET: Hospitals/Edit/5
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var hospital = await _context.Hospitals.FindAsync(id);
            if (hospital == null)
            {
                return NotFound();
            }
            return View(hospital);
        }

        // POST: Hospitals/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Edit(int id, [Bind("HospitalId,HospitalName,HospitalPhoneNumber,HospitalAdress,HospitalPhoto")] Hospital hospital)
        {
            if (id != hospital.HospitalId)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(hospital);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!HospitalExists(hospital.HospitalId))
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
            return View(hospital);
        }

        // GET: Hospitals/Delete/5
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var hospital = await _context.Hospitals
                .FirstOrDefaultAsync(m => m.HospitalId == id);
            if (hospital == null)
            {
                return NotFound();
            }

            return View(hospital);
        }

        // POST: Hospitals/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var hospital = await _context.Hospitals.FindAsync(id);
            _context.Hospitals.Remove(hospital);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool HospitalExists(int id)
        {
            return _context.Hospitals.Any(e => e.HospitalId == id);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        [Authorize(Roles = "admin")]
        public async Task<IActionResult> Import(IFormFile fileExcel)
        {
            if (ModelState.IsValid)
            {
                if (fileExcel != null)
                {
                    using (var stream = new FileStream(fileExcel.FileName, FileMode.Create))
                    {
                        await fileExcel.CopyToAsync(stream);
                        using (XLWorkbook workBook = new XLWorkbook(stream, XLEventTracking.Disabled))
                        {
                            //перегляд усіх листів (в даному випадку категорій)
                            foreach (IXLWorksheet worksheet in workBook.Worksheets)
                            {
                                //worksheet.Name - назва категорії. Пробуємо знайти в БД, якщо відсутня, то створюємо нову
                                Hospital newhospital;
                                var h = (from cat in _context.Hospitals
                                         where cat.HospitalName == worksheet.Name
                                         select cat).ToList();
                                if (h.Count > 0)
                                {
                                    newhospital = h[0];

                                    //перегляд усіх рядків                    
                                    foreach (IXLRow row in worksheet.RowsUsed().Skip(1))
                                    {
                                        try
                                        {
                                            Doctor doctor = new Doctor();
                                            doctor.DoctorName = row.Cell(1).Value.ToString();
                                            doctor.DoctorPhoneNumber = Convert.ToInt32(row.Cell(2).Value.ToString());
                                            doctor.DateStartWork = row.Cell(3).Value.ToString();
                                            doctor.Education = row.Cell(4).Value.ToString();
                                            doctor.Hospital = newhospital;
                                            _context.Doctors.Add(doctor);
                                            Console.WriteLine("doctor: " + doctor.DoctorName);
                                            //у разі наявності автора знайти його, у разі відсутності - додати
                                            /*for (int i = 2; i <= 5; i++)
                                            {
                                                if (row.Cell(i).Value.ToString().Length > 0)
                                                {
                                                    Patient author;

                                                    var a = (from aut in _context.Patients
                                                             where aut.PatientName.Contains(row.Cell(i).Value.ToString())
                                                             select aut).ToList();
                                                    if (a.Count > 0)
                                                    {
                                                        author = a[0];
                                                    }
                                                    else
                                                    {
                                                        author = new Patient();
                                                        author.PatientName = row.Cell(i).Value.ToString();
                                                        author.HomeAdress = "from EXCEL";
                                                        //додати в контекст
                                                        _context.Add(author);
                                                    }
                                                    DoctorsPatients ab = new AuthorsBooks();
                                                    ab.Book = book;
                                                    ab.Author = author;
                                                    _context.AuthorsBooks.Add(ab);
                                                }
                                            }*/
                                        }
                                        catch (Exception e)
                                        {
                                            //logging самостійно :)
                                            Console.WriteLine("Exception: " + e.Message);
                                        }
                                    }
                                }
                                else
                                {
                                    Console.WriteLine("No hospital");
                                    /*newcat = new Hospital();
                                    newcat.HospitalName = worksheet.Name;
                                    //newcat.Info = "from EXCEL";
                                    //додати в контекст
                                    _context.Hospitals.Add(newcat);*/
                                }
                            }
                        }
                    }
                }

                await _context.SaveChangesAsync();
            }
            return RedirectToAction(nameof(Index));
        }

        public ActionResult Export()
        {
            using (XLWorkbook workbook = new XLWorkbook(XLEventTracking.Disabled))
            {
                var hospitals = _context.Hospitals.Include("Doctors").ToList();
                //тут, для прикладу ми пишемо усі книжки з БД, в своїх проектах ТАК НЕ РОБИТИ (писати лише вибрані)
                foreach (var c in hospitals)
                {
                    var worksheet = workbook.Worksheets.Add(c.HospitalName);

                    worksheet.Cell("A1").Value = "Ім'я";
                    worksheet.Cell("B1").Value = "Номер телефона";
                    worksheet.Cell("C1").Value = "Дата початку роботи";
                    worksheet.Cell("D1").Value = "Освіта";
                    worksheet.Row(1).Style.Font.Bold = true;
                    var doctors = c.Doctors.ToList();

                    //нумерація рядків/стовпчиків починається з індекса 1 (не 0)
                    for (int i = 0; i < doctors.Count; i++)
                    {
                        worksheet.Cell(i + 2, 1).Value = doctors[i].DoctorName;
                        worksheet.Cell(i + 2, 2).Value = doctors[i].DoctorPhoneNumber;
                        worksheet.Cell(i + 2, 3).Value = doctors[i].DateStartWork;
                        worksheet.Cell(i + 2, 4).Value = doctors[i].Education;

                        /*var ab = _context.AuthorsBooks.Where(a => a.BookId == doctors[i].Id).Include("Author").ToList();
                        //більше 4-ох нікуди писати
                        int j = 0;
                        foreach (var a in ab)
                        {
                            if (j < 5)
                            {
                                worksheet.Cell(i + 2, j + 2).Value = a.Author.Name;
                                j++;
                            }
                        }*/

                    }
                }
                using (var stream = new MemoryStream())
                {
                    workbook.SaveAs(stream);
                    stream.Flush();

                    return new FileContentResult(stream.ToArray(),
                        "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet")
                    {
                        FileDownloadName = $"library_{DateTime.UtcNow.ToShortDateString()}.xlsx"
                    };
                }
            }
        }

    }
}
