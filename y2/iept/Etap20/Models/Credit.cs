using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Etap20.Models
{
    public class Credit
    {
        public Credit()
        {

        }

        public int CreditId { get; set; }
        public int ClientId { get; set; }
        public int CurrencyId { get; set; }
        public decimal Sum { get; set; }
        public decimal Percent { get; set; }
        public DateTime DateStart { get; set; }
        public decimal AmountPaid { get; set; }

        public virtual Client Client { get; set; }
        public virtual Currency Currency { get; set; }
    }
}
