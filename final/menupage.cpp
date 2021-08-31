#include "menupage.h"

using namespace System;
using namespace System::Windows::Forms;

[System::STAThread]void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	final::menupage a;
	Application::Run(%a);
}