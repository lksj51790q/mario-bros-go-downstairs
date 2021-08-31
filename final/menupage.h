#pragma once
#include "form_chart.h"
#include "form_setting.h"
#include "game.h"
namespace final {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// menupage 的摘要
	/// </summary>
	public ref class menupage : public System::Windows::Forms::Form
	{
	public:
		


		menupage(void)
		{
			InitializeComponent();

			//sound
			sound_button_mouse_enter = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\mouse_on_button.wav");
			sound_button_click = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\click_button.wav");
			
			//music
			this->axWindowsMediaPlayer_background_music->settings->autoStart = false;
			this->axWindowsMediaPlayer_background_music->settings->volume = 100;
			this->axWindowsMediaPlayer_background_music->settings->setMode("loop", true);
			this->axWindowsMediaPlayer_background_music->URL = Application::StartupPath + "\\music\\menu.wav";
			
			//image
			image_button = gcnew array<Image^>(2);
			image_button[0] = Image::FromFile(Application::StartupPath + "\\img\\menupage_button.png");
			image_button[1] = Image::FromFile(Application::StartupPath + "\\img\\menupage_button_mouse_enter.png");

			//setting
			set_music = gcnew bool();
			set_sound = gcnew bool();
			set_item = gcnew bool();
			set_invincible = gcnew bool();
			set_diffculty = gcnew Byte();

			//get setting
			refresh_setting();

			if (*set_music)
			{//play_background_music
				this->axWindowsMediaPlayer_background_music->Ctlcontrols->play();
			}
			
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~menupage()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button_chart;
	private: System::Windows::Forms::Button^  button_setting;
	private: System::Windows::Forms::Button^  button_exit;
	private: System::Windows::Forms::Button^  button_single;
	private: System::Windows::Forms::Button^  buttom_double;
	private: System::Windows::Forms::PictureBox^  pictureBox_title;
	private: System::Windows::Forms::PictureBox^  pictureBox_2p_ctrl;
	private: System::Windows::Forms::PictureBox^  pictureBox_1p_ctrl;
	private: System::Windows::Forms::PictureBox^  pictureBox_2p;
	private: System::Windows::Forms::PictureBox^  pictureBox_1p;
	private: AxWMPLib::AxWindowsMediaPlayer^  axWindowsMediaPlayer_background_music;




	private:
		/// <summary>
		/// 設計工具所需的變數。
		bool^ set_music = nullptr;
		bool^ set_sound = nullptr;
		bool^ set_item = nullptr;
		bool^ set_invincible = nullptr;
		Byte^ set_diffculty = nullptr;
		array<Image^>^ image_button = nullptr;
		System::Media::SoundPlayer^ sound_button_mouse_enter = nullptr;
		System::Media::SoundPlayer^ sound_button_click = nullptr;
	

		//function
		void refresh_setting()
		{
			array<String^>^ buffer = gcnew array<String^>(28);
			int i = 0;
			try
			{
				StreamReader^ fin = gcnew StreamReader("setting.txt");
				try
				{
					while ((buffer[i] = fin->ReadLine()) != "setting")
					{
						if (i == 0 && buffer[i] != "name")
							throw;
						else if (i == 11 && buffer[i] != "score")
							throw;
						else if (i > 11 && buffer[i] != "-")
						{
							Int32::Parse(buffer[i]);
						}
						i++;
					}
					*set_music = bool::Parse(fin->ReadLine());
					*set_sound = bool::Parse(fin->ReadLine());
					*set_item = bool::Parse(fin->ReadLine());
					*set_invincible = bool::Parse(fin->ReadLine());
					*set_diffculty = Byte::Parse(fin->ReadLine());
					fin->Close();
				}
				catch (Exception^ e)
				{
					fin->Close();

					int a = 10;
					StreamWriter ^fnew = gcnew StreamWriter("setting.txt");
					fnew->WriteLine("name");
					while (a > 0)
					{
						fnew->WriteLine("-");
						a--;
					}
					a = 10;
					fnew->WriteLine("score");
					while (a > 0)
					{
						fnew->WriteLine("-");
						a--;
					}
					fnew->WriteLine("setting");
					fnew->WriteLine("true");
					fnew->WriteLine("true");
					fnew->WriteLine("true");
					fnew->WriteLine("false");
					fnew->WriteLine("1");
					*set_music = true;
					*set_sound = true;
					*set_item = true;
					*set_invincible = false;
					*set_diffculty = 1;
					fnew->Close();
				}
			}
			catch (Exception^ e)
			{
				int a = 10;
				StreamWriter ^fnew = gcnew StreamWriter("setting.txt");
				fnew->WriteLine("name");
				while (a > 0)
				{
					fnew->WriteLine("-");
					a--;
				}
				a = 10;
				fnew->WriteLine("score");
				while (a > 0)
				{
					fnew->WriteLine("-");
					a--;
				}
				fnew->WriteLine("setting");
				fnew->WriteLine("true");
				fnew->WriteLine("true");
				fnew->WriteLine("true");
				fnew->WriteLine("false");
				fnew->WriteLine("1");
				*set_music = true;
				*set_sound = true;
				*set_item = true;
				*set_invincible = false;
				*set_diffculty = 1;
				fnew->Close();
			}
			return;
		}
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(menupage::typeid));
			this->button_chart = (gcnew System::Windows::Forms::Button());
			this->button_setting = (gcnew System::Windows::Forms::Button());
			this->button_exit = (gcnew System::Windows::Forms::Button());
			this->button_single = (gcnew System::Windows::Forms::Button());
			this->buttom_double = (gcnew System::Windows::Forms::Button());
			this->pictureBox_title = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_2p_ctrl = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_1p_ctrl = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_2p = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_1p = (gcnew System::Windows::Forms::PictureBox());
			this->axWindowsMediaPlayer_background_music = (gcnew AxWMPLib::AxWindowsMediaPlayer());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_title))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_2p_ctrl))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_1p_ctrl))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_2p))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_1p))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer_background_music))->BeginInit();
			this->SuspendLayout();
			// 
			// button_chart
			// 
			this->button_chart->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_chart.BackgroundImage")));
			this->button_chart->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button_chart->FlatAppearance->BorderSize = 0;
			this->button_chart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_chart->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 16));
			this->button_chart->Location = System::Drawing::Point(230, 260);
			this->button_chart->Name = L"button_chart";
			this->button_chart->Size = System::Drawing::Size(120, 48);
			this->button_chart->TabIndex = 3;
			this->button_chart->Text = L"分數排行";
			this->button_chart->UseVisualStyleBackColor = true;
			this->button_chart->Click += gcnew System::EventHandler(this, &menupage::button_chart_Click);
			this->button_chart->MouseEnter += gcnew System::EventHandler(this, &menupage::button_chart_MouseEnter);
			this->button_chart->MouseLeave += gcnew System::EventHandler(this, &menupage::button_chart_MouseLeave);
			// 
			// button_setting
			// 
			this->button_setting->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_setting.BackgroundImage")));
			this->button_setting->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button_setting->FlatAppearance->BorderSize = 0;
			this->button_setting->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_setting->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 16));
			this->button_setting->Location = System::Drawing::Point(230, 330);
			this->button_setting->Name = L"button_setting";
			this->button_setting->Size = System::Drawing::Size(120, 48);
			this->button_setting->TabIndex = 4;
			this->button_setting->Text = L"遊戲設置";
			this->button_setting->UseVisualStyleBackColor = true;
			this->button_setting->Click += gcnew System::EventHandler(this, &menupage::button_setting_Click);
			this->button_setting->MouseEnter += gcnew System::EventHandler(this, &menupage::button_setting_MouseEnter);
			this->button_setting->MouseLeave += gcnew System::EventHandler(this, &menupage::button_setting_MouseLeave);
			// 
			// button_exit
			// 
			this->button_exit->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_exit.BackgroundImage")));
			this->button_exit->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button_exit->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->button_exit->FlatAppearance->BorderSize = 0;
			this->button_exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_exit->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 16));
			this->button_exit->Location = System::Drawing::Point(230, 400);
			this->button_exit->Name = L"button_exit";
			this->button_exit->Size = System::Drawing::Size(120, 48);
			this->button_exit->TabIndex = 5;
			this->button_exit->Text = L"離開遊戲";
			this->button_exit->UseVisualStyleBackColor = true;
			this->button_exit->Click += gcnew System::EventHandler(this, &menupage::exitbutton_Click);
			this->button_exit->MouseEnter += gcnew System::EventHandler(this, &menupage::button_exit_MouseEnter);
			this->button_exit->MouseLeave += gcnew System::EventHandler(this, &menupage::button_exit_MouseLeave);
			// 
			// button_single
			// 
			this->button_single->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_single.BackgroundImage")));
			this->button_single->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button_single->FlatAppearance->BorderSize = 0;
			this->button_single->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_single->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 16));
			this->button_single->Location = System::Drawing::Point(230, 120);
			this->button_single->Name = L"button_single";
			this->button_single->Size = System::Drawing::Size(120, 48);
			this->button_single->TabIndex = 1;
			this->button_single->Text = L"單人挑戰";
			this->button_single->UseVisualStyleBackColor = true;
			this->button_single->Click += gcnew System::EventHandler(this, &menupage::button_single_Click);
			this->button_single->MouseEnter += gcnew System::EventHandler(this, &menupage::button_single_MouseEnter);
			this->button_single->MouseLeave += gcnew System::EventHandler(this, &menupage::button_single_MouseLeave);
			// 
			// buttom_double
			// 
			this->buttom_double->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttom_double.BackgroundImage")));
			this->buttom_double->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->buttom_double->FlatAppearance->BorderSize = 0;
			this->buttom_double->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttom_double->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 16));
			this->buttom_double->Location = System::Drawing::Point(230, 190);
			this->buttom_double->Name = L"buttom_double";
			this->buttom_double->Size = System::Drawing::Size(120, 48);
			this->buttom_double->TabIndex = 2;
			this->buttom_double->Text = L"雙人競賽";
			this->buttom_double->UseVisualStyleBackColor = true;
			this->buttom_double->Click += gcnew System::EventHandler(this, &menupage::buttom_double_Click);
			this->buttom_double->MouseEnter += gcnew System::EventHandler(this, &menupage::buttom_double_MouseEnter);
			this->buttom_double->MouseLeave += gcnew System::EventHandler(this, &menupage::buttom_double_MouseLeave);
			// 
			// pictureBox_title
			// 
			this->pictureBox_title->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_title->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_title.Image")));
			this->pictureBox_title->Location = System::Drawing::Point(183, 12);
			this->pictureBox_title->Name = L"pictureBox_title";
			this->pictureBox_title->Size = System::Drawing::Size(216, 83);
			this->pictureBox_title->TabIndex = 6;
			this->pictureBox_title->TabStop = false;
			// 
			// pictureBox_2p_ctrl
			// 
			this->pictureBox_2p_ctrl->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_2p_ctrl->Enabled = false;
			this->pictureBox_2p_ctrl->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_2p_ctrl.Image")));
			this->pictureBox_2p_ctrl->Location = System::Drawing::Point(12, 98);
			this->pictureBox_2p_ctrl->Name = L"pictureBox_2p_ctrl";
			this->pictureBox_2p_ctrl->Size = System::Drawing::Size(187, 169);
			this->pictureBox_2p_ctrl->TabIndex = 7;
			this->pictureBox_2p_ctrl->TabStop = false;
			this->pictureBox_2p_ctrl->Visible = false;
			// 
			// pictureBox_1p_ctrl
			// 
			this->pictureBox_1p_ctrl->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_1p_ctrl->Enabled = false;
			this->pictureBox_1p_ctrl->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_1p_ctrl.Image")));
			this->pictureBox_1p_ctrl->Location = System::Drawing::Point(385, 98);
			this->pictureBox_1p_ctrl->Name = L"pictureBox_1p_ctrl";
			this->pictureBox_1p_ctrl->Size = System::Drawing::Size(187, 169);
			this->pictureBox_1p_ctrl->TabIndex = 8;
			this->pictureBox_1p_ctrl->TabStop = false;
			this->pictureBox_1p_ctrl->Visible = false;
			// 
			// pictureBox_2p
			// 
			this->pictureBox_2p->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_2p->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_2p.Image")));
			this->pictureBox_2p->Location = System::Drawing::Point(2, 273);
			this->pictureBox_2p->Name = L"pictureBox_2p";
			this->pictureBox_2p->Size = System::Drawing::Size(74, 187);
			this->pictureBox_2p->TabIndex = 10;
			this->pictureBox_2p->TabStop = false;
			// 
			// pictureBox_1p
			// 
			this->pictureBox_1p->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_1p->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_1p.Image")));
			this->pictureBox_1p->Location = System::Drawing::Point(506, 288);
			this->pictureBox_1p->Name = L"pictureBox_1p";
			this->pictureBox_1p->Size = System::Drawing::Size(76, 172);
			this->pictureBox_1p->TabIndex = 9;
			this->pictureBox_1p->TabStop = false;
			// 
			// axWindowsMediaPlayer_background_music
			// 
			this->axWindowsMediaPlayer_background_music->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			this->axWindowsMediaPlayer_background_music->Enabled = true;
			this->axWindowsMediaPlayer_background_music->Location = System::Drawing::Point(408, 370);
			this->axWindowsMediaPlayer_background_music->Name = L"axWindowsMediaPlayer_background_music";
			this->axWindowsMediaPlayer_background_music->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^>(resources->GetObject(L"axWindowsMediaPlayer_background_music.OcxState")));
			this->axWindowsMediaPlayer_background_music->Size = System::Drawing::Size(75, 23);
			this->axWindowsMediaPlayer_background_music->TabIndex = 11;
			this->axWindowsMediaPlayer_background_music->TabStop = false;
			this->axWindowsMediaPlayer_background_music->Visible = false;
			// 
			// menupage
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ClientSize = System::Drawing::Size(584, 461);
			this->Controls->Add(this->axWindowsMediaPlayer_background_music);
			this->Controls->Add(this->pictureBox_2p);
			this->Controls->Add(this->pictureBox_1p);
			this->Controls->Add(this->pictureBox_1p_ctrl);
			this->Controls->Add(this->pictureBox_2p_ctrl);
			this->Controls->Add(this->pictureBox_title);
			this->Controls->Add(this->buttom_double);
			this->Controls->Add(this->button_single);
			this->Controls->Add(this->button_exit);
			this->Controls->Add(this->button_setting);
			this->Controls->Add(this->button_chart);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"menupage";
			this->Text = L"瑪莉歐兄弟下樓梯";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_title))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_2p_ctrl))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_1p_ctrl))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_2p))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_1p))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer_background_music))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void exitbutton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*set_sound)
		sound_button_click->Play();
	this->Close();
}
private: System::Void button_single_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*set_sound)
		sound_button_click->Play();
	if (*set_music)
	{
		this->axWindowsMediaPlayer_background_music->Ctlcontrols->stop();
	}
	game ^a = gcnew game(false, *set_music, *set_sound, *set_item, *set_invincible, *set_diffculty);
	this->Hide();
	a->ShowDialog();
	this->Show();
	delete a;
	if (*set_music)
	{
		this->axWindowsMediaPlayer_background_music->Ctlcontrols->play();
	}
}
private: System::Void buttom_double_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*set_sound)
		sound_button_click->Play();
	if (*set_music)
	{
		this->axWindowsMediaPlayer_background_music->Ctlcontrols->stop();
	}
	game ^a = gcnew game(true, *set_music, *set_sound, *set_item, *set_invincible, *set_diffculty);
	this->Hide();
	a->ShowDialog();
	this->Show();
	delete a;
	if (*set_music)
	{
		this->axWindowsMediaPlayer_background_music->Ctlcontrols->play();
	}
}
private: System::Void button_chart_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*set_sound)
		sound_button_click->Play();
	form_chart ^a = gcnew form_chart(*set_sound);
	this->Hide();
	a->ShowDialog();
	this->Show();
	delete a;
}
private: System::Void button_setting_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*set_sound)
		sound_button_click->Play();
	form_setting ^a = gcnew form_setting(*set_sound);
	this->Hide();
	a->ShowDialog();
	this->Show();
	delete a;
	refresh_setting();
	if (*set_music)
	{
		this->axWindowsMediaPlayer_background_music->Ctlcontrols->play();
	}
	else
	{
		this->axWindowsMediaPlayer_background_music->Ctlcontrols->stop();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
public:  virtual void OnPaint(PaintEventArgs^ e) override {

	//繼承動作
	__super::OnPaint(e);

	if (this->pictureBox_1p_ctrl->Enabled)
	{
		e->Graphics->DrawImage(this->pictureBox_1p_ctrl->Image, this->pictureBox_1p_ctrl->Location.X, this->pictureBox_1p_ctrl->Location.Y, this->pictureBox_1p_ctrl->Width, this->pictureBox_1p_ctrl->Height);
	}
	if (this->pictureBox_2p_ctrl->Enabled)
	{
		e->Graphics->DrawImage(this->pictureBox_2p_ctrl->Image, this->pictureBox_2p_ctrl->Location.X, this->pictureBox_2p_ctrl->Location.Y, this->pictureBox_2p_ctrl->Width, this->pictureBox_2p_ctrl->Height);
	}


}
private: System::Void button_single_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	this->pictureBox_1p_ctrl->Enabled = true;
	this->button_single->BackgroundImage = image_button[1];
	this->Refresh();
	if (*set_sound)
		sound_button_mouse_enter->Play();
}
private: System::Void button_single_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
	this->pictureBox_1p_ctrl->Enabled = false;
	this->button_single->BackgroundImage = image_button[0];
	this->Refresh();
}
private: System::Void buttom_double_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	this->pictureBox_1p_ctrl->Enabled = true;
	this->pictureBox_2p_ctrl->Enabled = true;
	this->buttom_double->BackgroundImage = image_button[1];
	this->Refresh();
	if (*set_sound)
		sound_button_mouse_enter->Play();
}
private: System::Void buttom_double_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
	this->pictureBox_1p_ctrl->Enabled = false;
	this->pictureBox_2p_ctrl->Enabled = false;
	this->buttom_double->BackgroundImage = image_button[0];
	this->Refresh();
}
private: System::Void button_chart_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	this->button_chart->BackgroundImage = image_button[1];
	if (*set_sound)
		sound_button_mouse_enter->Play();
}
private: System::Void button_chart_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
	this->button_chart->BackgroundImage = image_button[0];
}
private: System::Void button_setting_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	this->button_setting->BackgroundImage = image_button[1];
	if (*set_sound)
		sound_button_mouse_enter->Play();
}
private: System::Void button_setting_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
	this->button_setting->BackgroundImage = image_button[0];
}
private: System::Void button_exit_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	this->button_exit->BackgroundImage = image_button[1];
	if (*set_sound)
		sound_button_mouse_enter->Play();
}
private: System::Void button_exit_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
	this->button_exit->BackgroundImage = image_button[0];
}

};
}
