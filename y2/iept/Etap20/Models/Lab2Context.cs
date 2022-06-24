using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Etap20.Models
{
    public class Lab2Context : DbContext
    {
        public virtual DbSet<Currency> Currencies { get; set; }
        public virtual DbSet<Credit> Credits { get; set; }
        public virtual DbSet<Client> Clients { get; set; }
        public virtual DbSet<Bank> Banks { get; set; }

        public Lab2Context (DbContextOptions<Lab2Context> options) : base(options)
        {
            Database.EnsureCreated();
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Client>()
                .HasOne(p => p.Bank)
                .WithMany(b => b.Clients)
                .OnDelete(DeleteBehavior.Cascade)
                .IsRequired()
                .HasForeignKey(p => p.BankId);
        }
    }
}
