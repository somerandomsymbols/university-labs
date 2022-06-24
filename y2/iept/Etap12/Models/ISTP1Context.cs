using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;

#nullable disable

namespace Etap12
{
    public partial class ISTP1Context : DbContext
    {
        public ISTP1Context()
        {
        }

        public ISTP1Context(DbContextOptions<ISTP1Context> options)
            : base(options)
        {
        }

        public virtual DbSet<ArchiveEntry> ArchiveEntries { get; set; }
        public virtual DbSet<Disease> Diseases { get; set; }
        public virtual DbSet<Doctor> Doctors { get; set; }
        public virtual DbSet<Hospital> Hospitals { get; set; }
        public virtual DbSet<Insurance> Insurances { get; set; }
        public virtual DbSet<Patient> Patients { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
#warning To protect potentially sensitive information in your connection string, you should move it out of source code. You can avoid scaffolding the connection string by using the Name= syntax to read it from configuration - see https://go.microsoft.com/fwlink/?linkid=2131148. For more guidance on storing connection strings, see http://go.microsoft.com/fwlink/?LinkId=723263.
                optionsBuilder.UseSqlServer("Server= LAPTOP-BOP5U79R; Database=ISTP1; Trusted_Connection=True; ");
            }
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.HasAnnotation("Relational:Collation", "Cyrillic_General_CI_AS");

            modelBuilder.Entity<ArchiveEntry>(entity =>
            {
                entity.HasKey(e => e.EntryId);

                entity.Property(e => e.EntryId).HasColumnName("EntryID");

                entity.Property(e => e.BeginningDate)
                    .IsRequired()
                    .HasMaxLength(50);

                entity.Property(e => e.DiagnosisId).HasColumnName("DiagnosisID");

                entity.Property(e => e.EndingDate)
                    .IsRequired()
                    .HasMaxLength(50);

                entity.Property(e => e.PatientId).HasColumnName("PatientID");

                entity.HasOne(d => d.Diagnosis)
                    .WithMany(p => p.ArchiveEntries)
                    .HasForeignKey(d => d.DiagnosisId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("FK_ArchiveEntries_Diseases");

                entity.HasOne(d => d.Patient)
                    .WithMany(p => p.ArchiveEntries)
                    .HasForeignKey(d => d.PatientId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("FK_ArchiveEntries_Patients");
            });

            modelBuilder.Entity<Disease>(entity =>
            {
                entity.HasKey(e => e.DiagnosisId);

                entity.Property(e => e.DiagnosisId).HasColumnName("DiagnosisID");

                entity.Property(e => e.Recomendations)
                    .IsRequired()
                    .HasMaxLength(50);

                entity.Property(e => e.Symptoms)
                    .IsRequired()
                    .HasMaxLength(50);
            });

            modelBuilder.Entity<Doctor>(entity =>
            {
                entity.Property(e => e.DoctorId).HasColumnName("DoctorID");

                entity.Property(e => e.DateStartWork)
                    .IsRequired()
                    .HasMaxLength(50);

                entity.Property(e => e.DoctorName)
                    .IsRequired()
                    .HasMaxLength(50);

                entity.Property(e => e.Education)
                    .IsRequired()
                    .HasMaxLength(50);

                entity.Property(e => e.HospitalId).HasColumnName("HospitalID");

                entity.HasOne(d => d.Hospital)
                    .WithMany(p => p.Doctors)
                    .HasForeignKey(d => d.HospitalId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("FK_Doctors_Hospitals");
            });

            modelBuilder.Entity<Hospital>(entity =>
            {
                entity.Property(e => e.HospitalId).HasColumnName("HospitalID");

                entity.Property(e => e.HospitalAdress)
                    .IsRequired()
                    .HasMaxLength(50);

                entity.Property(e => e.HospitalName)
                    .IsRequired()
                    .HasMaxLength(50);
            });

            modelBuilder.Entity<Insurance>(entity =>
            {
                entity.Property(e => e.InsuranceId).HasColumnName("InsuranceID");

                entity.Property(e => e.InsuranceCases)
                    .IsRequired()
                    .HasMaxLength(50);

                entity.Property(e => e.PatientId).HasColumnName("PatientID");

                entity.HasOne(d => d.Patient)
                    .WithMany(p => p.Insurances)
                    .HasForeignKey(d => d.PatientId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("FK_Insurances_Patients");
            });

            modelBuilder.Entity<Patient>(entity =>
            {
                entity.Property(e => e.PatientId).HasColumnName("PatientID");

                entity.Property(e => e.DateOfBirth)
                    .IsRequired()
                    .HasMaxLength(50);

                entity.Property(e => e.DoctorId).HasColumnName("DoctorID");

                entity.Property(e => e.HomeAdress)
                    .IsRequired()
                    .HasMaxLength(50);

                entity.Property(e => e.PatientName)
                    .IsRequired()
                    .HasMaxLength(50);

                entity.HasOne(d => d.Doctor)
                    .WithMany(p => p.Patients)
                    .HasForeignKey(d => d.DoctorId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("FK_Patients_Doctors");
            });

            OnModelCreatingPartial(modelBuilder);
        }

        partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
    }
}
