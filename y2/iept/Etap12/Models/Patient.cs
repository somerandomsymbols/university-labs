using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

#nullable disable

namespace Etap12
{
    [Display(Name = "Пацієнт")]
    public partial class Patient
    {
        public Patient()
        {
            ArchiveEntries = new HashSet<ArchiveEntry>();
            Insurances = new HashSet<Insurance>();
        }

        public int PatientId { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "ПІБ пацієнта")]
        public string PatientName { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Дата народження")]
        public string DateOfBirth { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Домашня адреса")]
        public string HomeAdress { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Телефон пацієнта")]
        public int PatientPhoneNumber { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Range(0, 500, ErrorMessage = "Недопустимий зріст")]
        [Display(Name = "Зріст")]
        public double Height { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Range(0, 500, ErrorMessage = "Недопустима вага")]
        [Display(Name = "Вага")]
        public double Weight { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Посвідчення особи")]
        public string Passport { get; set; }
        public int DoctorId { get; set; }
        

        public virtual Doctor Doctor { get; set; }
        public virtual ICollection<ArchiveEntry> ArchiveEntries { get; set; }
        public virtual ICollection<Insurance> Insurances { get; set; }
    }
}
