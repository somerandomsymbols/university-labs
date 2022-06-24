using System;
using System.Collections.Generic;

#nullable disable

namespace Etap12
{
    public partial class ArchiveEntry
    {
        public int EntryId { get; set; }
        public int PatientId { get; set; }
        public int DiagnosisId { get; set; }
        public string BeginningDate { get; set; }
        public string EndingDate { get; set; }

        public virtual Disease Diagnosis { get; set; }
        public virtual Patient Patient { get; set; }
    }
}
