using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

#nullable disable

namespace Etap12
{
    [Display(Name = "Лікарня")]
    public partial class Hospital
    {
        public Hospital()
        {
            Doctors = new HashSet<Doctor>();
        }

        public int HospitalId { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Назва лікарні")]
        public string HospitalName { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Телефон лікарні")]
        public int HospitalPhoneNumber { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Адреса лікарні")]
        public string HospitalAdress { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Фото лікарні")]
        public string HospitalPhoto { get; set; }

        public virtual ICollection<Doctor> Doctors { get; set; }
    }
}
