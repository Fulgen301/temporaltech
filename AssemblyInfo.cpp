using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace Vintagestory::API::Common;

// General Information about an assembly is controlled through the following 
// set of attributes. Change these attribute values to modify the information
// associated with an assembly.
[assembly:AssemblyTitle("temporaltech")];
[assembly:AssemblyDescription("")] ;
//[assembly: AssemblyConfiguration("")]
[assembly:AssemblyCompany("")] ;
[assembly:AssemblyProduct("")] ;
[assembly:AssemblyCopyright("")] ;

[assembly:AssemblyTrademark("")] ;
[assembly:AssemblyCulture("")] ;

// Setting ComVisible to false makes the types in this assembly not visible 
// to COM components.  If you need to access a type in this assembly from 
// COM, set the ComVisible attribute to true on that type.
[assembly:ComVisible(false)];

// The following GUID is for the ID of the typelib if this project is exposed to COM
[assembly:Guid("2182ca81-e902-4591-9d49-03a33ef5f151")] ;

// Version information for an assembly consists of the following four values:
//
//      Major Version
//      Minor Version 
//      Build Number
//      Revision
//
// You can specify all the values or you can default the Build and Revision Numbers 
// by using the '*' as shown below:
[assembly:AssemblyVersion("1.0.*")];

[assembly:ModInfo("Temporal Tech", "temporaltech",
                  Version = "1.0.0",
                  Description = "Temporal technology",
                  Authors = gcnew array<System::String ^>{"Fulgen"},
                  RequiredOnClient = true
)] ;