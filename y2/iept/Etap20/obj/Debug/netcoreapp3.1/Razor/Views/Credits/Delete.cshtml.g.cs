#pragma checksum "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "6002582bd2fd47f489333a80a6133c7e770242b1"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(AspNetCore.Views_Credits_Delete), @"mvc.1.0.view", @"/Views/Credits/Delete.cshtml")]
namespace AspNetCore
{
    #line hidden
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Threading.Tasks;
    using Microsoft.AspNetCore.Mvc;
    using Microsoft.AspNetCore.Mvc.Rendering;
    using Microsoft.AspNetCore.Mvc.ViewFeatures;
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"6002582bd2fd47f489333a80a6133c7e770242b1", @"/Views/Credits/Delete.cshtml")]
    public class Views_Credits_Delete : global::Microsoft.AspNetCore.Mvc.Razor.RazorPage<Etap20.Models.Credit>
    {
        #pragma warning disable 1998
        public async override global::System.Threading.Tasks.Task ExecuteAsync()
        {
            WriteLiteral("\r\n");
#nullable restore
#line 3 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
  
    ViewData["Title"] = "Delete";

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n<h1>Delete</h1>\r\n\r\n<h3>Are you sure you want to delete this?</h3>\r\n<div>\r\n    <h4>Credit</h4>\r\n    <hr />\r\n    <dl class=\"row\">\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 15 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.Sum));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n        <dd class = \"col-sm-10\">\r\n            ");
#nullable restore
#line 18 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayFor(model => model.Sum));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dd>\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 21 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.Percent));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n        <dd class = \"col-sm-10\">\r\n            ");
#nullable restore
#line 24 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayFor(model => model.Percent));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dd>\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 27 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.DateStart));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n        <dd class = \"col-sm-10\">\r\n            ");
#nullable restore
#line 30 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayFor(model => model.DateStart));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dd>\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 33 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.AmountPaid));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n        <dd class = \"col-sm-10\">\r\n            ");
#nullable restore
#line 36 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayFor(model => model.AmountPaid));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dd>\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 39 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.Client));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n        <dd class = \"col-sm-10\">\r\n            ");
#nullable restore
#line 42 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayFor(model => model.Client.ClientId));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dd class>\r\n        <dt class = \"col-sm-2\">\r\n            ");
#nullable restore
#line 45 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayNameFor(model => model.Currency));

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n        </dt>\r\n        <dd class = \"col-sm-10\">\r\n            ");
#nullable restore
#line 48 "D:\c\kubick\ISTP\Etap20\Views\Credits\Delete.cshtml"
       Write(Html.DisplayFor(model => model.Currency.CurrencyId));

#line default
#line hidden
#nullable disable
            WriteLiteral(@"
        </dd class>
    </dl>
    
    <form asp-action=""Delete"">
        <input type=""hidden"" asp-for=""CreditId"" />
        <input type=""submit"" value=""Delete"" class=""btn btn-danger"" /> |
        <a asp-action=""Index"">Back to List</a>
    </form>
</div>
");
        }
        #pragma warning restore 1998
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.ViewFeatures.IModelExpressionProvider ModelExpressionProvider { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IUrlHelper Url { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IViewComponentHelper Component { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IJsonHelper Json { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IHtmlHelper<Etap20.Models.Credit> Html { get; private set; }
    }
}
#pragma warning restore 1591
