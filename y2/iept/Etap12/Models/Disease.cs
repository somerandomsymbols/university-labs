using System;
using System.Collections.Generic;

#nullable disable

namespace Etap12
{
    public partial class Disease
    {
        public Disease()
        {
            ArchiveEntries = new HashSet<ArchiveEntry>();
        }

        public int DiagnosisId { get; set; }
        public string Symptoms { get; set; }
        public string Recomendations { get; set; }

        public virtual ICollection<ArchiveEntry> ArchiveEntries { get; set; }
    }
}
