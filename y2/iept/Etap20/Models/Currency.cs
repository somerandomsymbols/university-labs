using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Etap20.Models
{
    public class Currency
    {
        public Currency()
        {
            Credits = new List<Credit>();
        }

        public int CurrencyId { get; set; }
        public string Name { get; set; }

        public virtual ICollection<Credit> Credits { get; set; }
    }
}
