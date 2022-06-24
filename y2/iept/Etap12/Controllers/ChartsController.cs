using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace Etap12.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ChartsController : ControllerBase
    {
        private readonly ISTP1Context _context;

        public ChartsController(ISTP1Context context)
        {
            _context = context;
        }

        [HttpGet("JsonData")]
        public JsonResult JsonData()
        {
            var hospitals = _context.Hospitals.Include(h => h.Doctors).ToList();
            var patients = _context.Patients.ToList();
            List<object> res = new List<object>();

            res.Add(new[] { "Лікарня", "Кількість пацієнтів" });

            foreach (var h in hospitals)
            {
                res.Add(new object[] { h.HospitalName, patients.Join(h.Doctors, p => p.DoctorId, d => d.DoctorId, (p, d) => p.PatientId).Count() });
            }

            return new JsonResult(res);
        }

        [HttpGet("PatientsData")]
        public JsonResult PatientsData()
        {
            var patients = _context.Patients.Include(p => p.Insurances).ToList();
            List<object> res = new List<object>();

            res.Add(new[] { "Пацієнт", "Загальна сума страхування" });

            foreach (var p in patients)
            {
                res.Add(new object[] { p.PatientName, p.Insurances.Select(i => i.Balance).Sum() });
            }

            return new JsonResult(res);
        }
    }
}
