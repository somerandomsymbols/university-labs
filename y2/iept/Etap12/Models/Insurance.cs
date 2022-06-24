using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

#nullable disable

namespace Etap12
{
    [Display(Name = "Страхування")] 
    public partial class Insurance
    {
        public int InsuranceId { get; set; }
        public int PatientId { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Range(0, 1000000, ErrorMessage = "Недопустима сума")]
        [Display(Name = "Сума на рахунку")]
        public double Balance { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Страхові випадки")]
        public string InsuranceCases { get; set; }

        public virtual Patient Patient { get; set; }
    }
}
