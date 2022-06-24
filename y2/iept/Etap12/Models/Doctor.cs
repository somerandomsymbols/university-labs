using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

#nullable disable

namespace Etap12
{
    [Display(Name = "Лікар")]
    public partial class Doctor
    {
        public Doctor()
        {
            Patients = new HashSet<Patient>();
        }

        public int DoctorId { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "ПІБ лікаря")]
        public string DoctorName { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Освіта лікаря")]
        public string Education { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Дата початку роботи")]
        public string DateStartWork { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Телефон лікаря")]
        public int DoctorPhoneNumber { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Фото")]
        public string DoctorPhoto { get; set; }
        public int HospitalId { get; set; }

        public virtual Hospital Hospital { get; set; }
        public virtual ICollection<Patient> Patients { get; set; }
    }
}
