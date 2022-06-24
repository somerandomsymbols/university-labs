using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.ComponentModel.DataAnnotations;

namespace Etap20.Models
{
    public class Bank
    {
        public Bank()
        {
            Clients = new List<Client>();
        }

        public int BankId { get; set; }
        [Required(ErrorMessage = "Поле не повинно бути порожнім")]
        [Display(Name = "Назва банку")]
        public string Name { get; set; }
        [Display(Name = "Телефон банку")]
        public string PhoneNumber { get; set; }
        [Display(Name = "Адреса банку")]
        public string Adress { get; set; }
        public virtual ICollection<Client> Clients { get; set; }
    }
}
