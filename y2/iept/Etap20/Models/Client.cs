using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace Etap20.Models
{
    public class Client
    {
        public Client()
        {
            Credits = new List<Credit>();
        }

        public int ClientId { get; set; }
        public int BankId { get; set; }
        public string Name { get; set; }
        public decimal Score { get; set; }
        public string PhoneNumber { get; set; }
        public string Adress { get; set; }

        public virtual Bank Bank { get; set; }
        public virtual ICollection<Credit> Credits { get; set; }
    }
}
