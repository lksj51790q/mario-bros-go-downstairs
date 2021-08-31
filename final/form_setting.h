#pragma once

namespace final {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	/// <summary>
	/// form_setting 的摘要
	/// </summary>
	public ref class form_setting : public System::Windows::Forms::Form
	{
	public:
		bool^ setting_sound;
		System::Media::SoundPlayer^ sound_button_mouse_enter = nullptr;
		System::Media::SoundPlayer^ sound_button_click = nullptr;

		bool ^set_music = gcnew bool();
		bool ^set_sound = gcnew bool();
		bool ^set_item = gcnew bool();
		bool ^set_invincible = gcnew bool();
		Byte ^set_diffculty = gcnew Byte();
		array<Image^>^ image_onoff = gcnew array<Image^>(2);
		array<Image^>^ image_difficulty = gcnew array<Image^>(6);
		array<Image^>^ image_button = gcnew array<Image^>(2);
		array<String^> ^buffer = gcnew array<String^>(24);

		form_setting(bool^ sound)
		{
			setting_sound = gcnew bool(*sound);
			if (*sound)
			{
				//sound
				sound_button_mouse_enter = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\mouse_on_button.wav");
				sound_button_click = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\click_button.wav");
			}


			image_onoff[0] = Image::FromFile(Application::StartupPath + "\\img\\click_on.png");
			image_onoff[1] = Image::FromFile(Application::StartupPath + "\\img\\click_off.png");
			image_difficulty[0] = Image::FromFile(Application::StartupPath + "\\img\\click_easy_on.png");
			image_difficulty[1] = Image::FromFile(Application::StartupPath + "\\img\\click_easy_off.png");
			image_difficulty[2] = Image::FromFile(Application::StartupPath + "\\img\\click_normal_on.png");
			image_difficulty[3] = Image::FromFile(Application::StartupPath + "\\img\\click_normal_off.png");
			image_difficulty[4] = Image::FromFile(Application::StartupPath + "\\img\\click_hard_on.png");
			image_difficulty[5] = Image::FromFile(Application::StartupPath + "\\img\\click_hard_off.png");
			image_button[0] = Image::FromFile(Application::StartupPath + "\\img\\setting_button.png");
			image_button[1] = Image::FromFile(Application::StartupPath + "\\img\\setting_button_mouse_enter.png");
			StreamReader^ fin = gcnew StreamReader("setting.txt");
			int i = 0;
			while ((buffer[i] = fin->ReadLine()) != "setting")
			{
				i++;
			}
			*set_music = bool::Parse(fin->ReadLine());
			*set_sound = bool::Parse(fin->ReadLine());
			*set_item = bool::Parse(fin->ReadLine());
			*set_invincible = bool::Parse(fin->ReadLine());
			*set_diffculty = Byte::Parse(fin->ReadLine());
			fin->Close();
			delete fin;
			InitializeComponent();
			if (*set_music == true)
			{
				this->button_music_set->Dock = System::Windows::Forms::DockStyle::Left;
				this->button_music_set->BackgroundImage = image_onoff[0];
			}
			else
			{
				this->button_music_set->Dock = System::Windows::Forms::DockStyle::Right;
				this->button_music_set->BackgroundImage = image_onoff[1];
			}
			if (*set_sound == true)
			{
				this->button_sound_set->Dock = System::Windows::Forms::DockStyle::Left;
				this->button_sound_set->BackgroundImage = image_onoff[0];
			}
			else
			{
				this->button_sound_set->Dock = System::Windows::Forms::DockStyle::Right;
				this->button_sound_set->BackgroundImage =image_onoff[1];
			}
			if (*set_item == true)
			{
				this->button_item_set->Dock = System::Windows::Forms::DockStyle::Left;
				this->button_item_set->BackgroundImage =image_onoff[0];
			}
			else
			{
				this->button_item_set->Dock = System::Windows::Forms::DockStyle::Right;
				this->button_item_set->BackgroundImage =image_onoff[1];
			}
			if (*set_invincible == true)
			{
				this->button_invincible_set->Dock = System::Windows::Forms::DockStyle::Left;
				this->button_invincible_set->BackgroundImage = image_onoff[0];
			}
			else
			{
				this->button_invincible_set->Dock = System::Windows::Forms::DockStyle::Right;
				this->button_invincible_set->BackgroundImage = image_onoff[1];
			}


			this->button_difficulty_easy->BackgroundImage = image_difficulty[1];
			this->button_difficulty_normal->BackgroundImage = image_difficulty[3];
			this->button_difficulty_hard->BackgroundImage = image_difficulty[5];
			if (*set_diffculty == 1)
			{
				this->button_difficulty_easy->BackgroundImage = image_difficulty[0];
			}

			else if(*set_diffculty == 2) 
			{
				this->button_difficulty_normal->BackgroundImage = image_difficulty[2];
			}
			else 
			{
				this->button_difficulty_hard->BackgroundImage = image_difficulty[4];
			}
			//
			//TODO:  在此加入建構函式程式碼
			//
		}
	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~form_setting()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox_title;


	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button_music_set;
	private: System::Windows::Forms::Panel^  panel_music_set;
private: System::Windows::Forms::Panel^  panel_sound;




	private: System::Windows::Forms::Button^  button_sound_set;


private: System::Windows::Forms::Panel^  panel_item;

	private: System::Windows::Forms::Button^  button_item_set;


private: System::Windows::Forms::Panel^  panel_invincible;

	private: System::Windows::Forms::Button^  button_invincible_set;


	private: System::Windows::Forms::Button^  button_save;
	private: System::Windows::Forms::Button^  button_cancel;
	private: System::Windows::Forms::Button^  button_reset;
private: System::Windows::Forms::Panel^  panel_difficulty;

	private: System::Windows::Forms::Button^  button_difficulty_easy;
	private: System::Windows::Forms::Button^  button_difficulty_normal;
	private: System::Windows::Forms::Button^  button_difficulty_hard;


	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(form_setting::typeid));
			this->pictureBox_title = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button_music_set = (gcnew System::Windows::Forms::Button());
			this->panel_music_set = (gcnew System::Windows::Forms::Panel());
			this->panel_sound = (gcnew System::Windows::Forms::Panel());
			this->button_sound_set = (gcnew System::Windows::Forms::Button());
			this->button_invincible_set = (gcnew System::Windows::Forms::Button());
			this->panel_item = (gcnew System::Windows::Forms::Panel());
			this->button_item_set = (gcnew System::Windows::Forms::Button());
			this->panel_invincible = (gcnew System::Windows::Forms::Panel());
			this->button_save = (gcnew System::Windows::Forms::Button());
			this->button_cancel = (gcnew System::Windows::Forms::Button());
			this->button_reset = (gcnew System::Windows::Forms::Button());
			this->panel_difficulty = (gcnew System::Windows::Forms::Panel());
			this->button_difficulty_hard = (gcnew System::Windows::Forms::Button());
			this->button_difficulty_normal = (gcnew System::Windows::Forms::Button());
			this->button_difficulty_easy = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_title))->BeginInit();
			this->panel_music_set->SuspendLayout();
			this->panel_sound->SuspendLayout();
			this->panel_item->SuspendLayout();
			this->panel_invincible->SuspendLayout();
			this->panel_difficulty->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox_title
			// 
			this->pictureBox_title->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_title->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_title.Image")));
			this->pictureBox_title->Location = System::Drawing::Point(305, 45);
			this->pictureBox_title->Name = L"pictureBox_title";
			this->pictureBox_title->Size = System::Drawing::Size(89, 42);
			this->pictureBox_title->TabIndex = 0;
			this->pictureBox_title->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->label1->Location = System::Drawing::Point(195, 130);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(110, 31);
			this->label1->TabIndex = 4;
			this->label1->Text = L"背景音樂";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->label2->Location = System::Drawing::Point(195, 190);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(110, 31);
			this->label2->TabIndex = 5;
			this->label2->Text = L"遊戲音效";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold));
			this->label3->ForeColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->label3->Location = System::Drawing::Point(217, 370);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(62, 31);
			this->label3->TabIndex = 6;
			this->label3->Text = L"難度";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->label4->Location = System::Drawing::Point(217, 310);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(62, 31);
			this->label4->TabIndex = 7;
			this->label4->Text = L"無敵";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold));
			this->label5->ForeColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->label5->Location = System::Drawing::Point(217, 250);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(62, 31);
			this->label5->TabIndex = 8;
			this->label5->Text = L"道具";
			// 
			// button_music_set
			// 
			this->button_music_set->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_music_set.BackgroundImage")));
			this->button_music_set->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button_music_set->Dock = System::Windows::Forms::DockStyle::Left;
			this->button_music_set->FlatAppearance->BorderSize = 0;
			this->button_music_set->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_music_set->ForeColor = System::Drawing::Color::Red;
			this->button_music_set->Location = System::Drawing::Point(0, 0);
			this->button_music_set->Name = L"button_music_set";
			this->button_music_set->Size = System::Drawing::Size(48, 48);
			this->button_music_set->TabIndex = 15;
			this->button_music_set->UseVisualStyleBackColor = true;
			// 
			// panel_music_set
			// 
			this->panel_music_set->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel_music_set.BackgroundImage")));
			this->panel_music_set->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->panel_music_set->Controls->Add(this->button_music_set);
			this->panel_music_set->Location = System::Drawing::Point(395, 121);
			this->panel_music_set->Name = L"panel_music_set";
			this->panel_music_set->Size = System::Drawing::Size(93, 48);
			this->panel_music_set->TabIndex = 16;
			this->panel_music_set->Click += gcnew System::EventHandler(this, &form_setting::panel_music_set_Click);
			// 
			// panel_sound
			// 
			this->panel_sound->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel_sound.BackgroundImage")));
			this->panel_sound->Controls->Add(this->button_sound_set);
			this->panel_sound->Location = System::Drawing::Point(395, 181);
			this->panel_sound->Name = L"panel_sound";
			this->panel_sound->Size = System::Drawing::Size(93, 48);
			this->panel_sound->TabIndex = 17;
			this->panel_sound->Click += gcnew System::EventHandler(this, &form_setting::panel_sound_Click);
			// 
			// button_sound_set
			// 
			this->button_sound_set->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_sound_set.BackgroundImage")));
			this->button_sound_set->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button_sound_set->Dock = System::Windows::Forms::DockStyle::Left;
			this->button_sound_set->FlatAppearance->BorderSize = 0;
			this->button_sound_set->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_sound_set->ForeColor = System::Drawing::Color::Red;
			this->button_sound_set->Location = System::Drawing::Point(0, 0);
			this->button_sound_set->Name = L"button_sound_set";
			this->button_sound_set->Size = System::Drawing::Size(48, 48);
			this->button_sound_set->TabIndex = 15;
			this->button_sound_set->UseVisualStyleBackColor = true;
			// 
			// button_invincible_set
			// 
			this->button_invincible_set->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_invincible_set.BackgroundImage")));
			this->button_invincible_set->Dock = System::Windows::Forms::DockStyle::Left;
			this->button_invincible_set->FlatAppearance->BorderSize = 0;
			this->button_invincible_set->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_invincible_set->ForeColor = System::Drawing::Color::Red;
			this->button_invincible_set->Location = System::Drawing::Point(0, 0);
			this->button_invincible_set->Name = L"button_invincible_set";
			this->button_invincible_set->Size = System::Drawing::Size(48, 48);
			this->button_invincible_set->TabIndex = 15;
			this->button_invincible_set->UseVisualStyleBackColor = true;
			// 
			// panel_item
			// 
			this->panel_item->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel_item.BackgroundImage")));
			this->panel_item->Controls->Add(this->button_item_set);
			this->panel_item->Location = System::Drawing::Point(395, 241);
			this->panel_item->Name = L"panel_item";
			this->panel_item->Size = System::Drawing::Size(93, 48);
			this->panel_item->TabIndex = 18;
			this->panel_item->Click += gcnew System::EventHandler(this, &form_setting::panel_item_Click);
			// 
			// button_item_set
			// 
			this->button_item_set->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_item_set.BackgroundImage")));
			this->button_item_set->Dock = System::Windows::Forms::DockStyle::Left;
			this->button_item_set->FlatAppearance->BorderSize = 0;
			this->button_item_set->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_item_set->ForeColor = System::Drawing::Color::Red;
			this->button_item_set->Location = System::Drawing::Point(0, 0);
			this->button_item_set->Name = L"button_item_set";
			this->button_item_set->Size = System::Drawing::Size(48, 48);
			this->button_item_set->TabIndex = 15;
			this->button_item_set->UseVisualStyleBackColor = true;
			// 
			// panel_invincible
			// 
			this->panel_invincible->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel_invincible.BackgroundImage")));
			this->panel_invincible->Controls->Add(this->button_invincible_set);
			this->panel_invincible->Location = System::Drawing::Point(395, 301);
			this->panel_invincible->Name = L"panel_invincible";
			this->panel_invincible->Size = System::Drawing::Size(93, 48);
			this->panel_invincible->TabIndex = 19;
			this->panel_invincible->Click += gcnew System::EventHandler(this, &form_setting::panel_invincible_Click);
			// 
			// button_save
			// 
			this->button_save->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_save.BackgroundImage")));
			this->button_save->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->button_save->FlatAppearance->BorderSize = 0;
			this->button_save->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_save->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button_save->Location = System::Drawing::Point(302, 443);
			this->button_save->Name = L"button_save";
			this->button_save->Size = System::Drawing::Size(96, 48);
			this->button_save->TabIndex = 1;
			this->button_save->Text = L"儲存";
			this->button_save->UseVisualStyleBackColor = true;
			this->button_save->Click += gcnew System::EventHandler(this, &form_setting::button_save_Click);
			this->button_save->MouseEnter += gcnew System::EventHandler(this, &form_setting::button_save_MouseEnter);
			this->button_save->MouseLeave += gcnew System::EventHandler(this, &form_setting::button_save_MouseLeave);
			// 
			// button_cancel
			// 
			this->button_cancel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_cancel.BackgroundImage")));
			this->button_cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button_cancel->FlatAppearance->BorderSize = 0;
			this->button_cancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_cancel->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button_cancel->Location = System::Drawing::Point(404, 443);
			this->button_cancel->Name = L"button_cancel";
			this->button_cancel->Size = System::Drawing::Size(96, 48);
			this->button_cancel->TabIndex = 2;
			this->button_cancel->Text = L"取消";
			this->button_cancel->UseVisualStyleBackColor = true;
			this->button_cancel->MouseEnter += gcnew System::EventHandler(this, &form_setting::button_cancel_MouseEnter);
			this->button_cancel->MouseLeave += gcnew System::EventHandler(this, &form_setting::button_cancel_MouseLeave);
			// 
			// button_reset
			// 
			this->button_reset->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_reset.BackgroundImage")));
			this->button_reset->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button_reset->FlatAppearance->BorderSize = 0;
			this->button_reset->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_reset->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button_reset->Location = System::Drawing::Point(200, 443);
			this->button_reset->Name = L"button_reset";
			this->button_reset->Size = System::Drawing::Size(96, 48);
			this->button_reset->TabIndex = 3;
			this->button_reset->Text = L"預設";
			this->button_reset->UseVisualStyleBackColor = true;
			this->button_reset->Click += gcnew System::EventHandler(this, &form_setting::button_reset_Click);
			this->button_reset->MouseEnter += gcnew System::EventHandler(this, &form_setting::button_reset_MouseEnter);
			this->button_reset->MouseLeave += gcnew System::EventHandler(this, &form_setting::button_reset_MouseLeave);
			// 
			// panel_difficulty
			// 
			this->panel_difficulty->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->panel_difficulty->Controls->Add(this->button_difficulty_hard);
			this->panel_difficulty->Controls->Add(this->button_difficulty_normal);
			this->panel_difficulty->Controls->Add(this->button_difficulty_easy);
			this->panel_difficulty->Location = System::Drawing::Point(305, 361);
			this->panel_difficulty->Name = L"panel_difficulty";
			this->panel_difficulty->Size = System::Drawing::Size(354, 48);
			this->panel_difficulty->TabIndex = 23;
			// 
			// button_difficulty_hard
			// 
			this->button_difficulty_hard->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_difficulty_hard.BackgroundImage")));
			this->button_difficulty_hard->FlatAppearance->BorderSize = 0;
			this->button_difficulty_hard->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_difficulty_hard->Location = System::Drawing::Point(234, 0);
			this->button_difficulty_hard->Name = L"button_difficulty_hard";
			this->button_difficulty_hard->Size = System::Drawing::Size(120, 48);
			this->button_difficulty_hard->TabIndex = 19;
			this->button_difficulty_hard->UseVisualStyleBackColor = true;
			this->button_difficulty_hard->Click += gcnew System::EventHandler(this, &form_setting::button_difficulty_hard_Click);
			// 
			// button_difficulty_normal
			// 
			this->button_difficulty_normal->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_difficulty_normal.BackgroundImage")));
			this->button_difficulty_normal->FlatAppearance->BorderSize = 0;
			this->button_difficulty_normal->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_difficulty_normal->Location = System::Drawing::Point(117, 0);
			this->button_difficulty_normal->Name = L"button_difficulty_normal";
			this->button_difficulty_normal->Size = System::Drawing::Size(120, 48);
			this->button_difficulty_normal->TabIndex = 18;
			this->button_difficulty_normal->UseVisualStyleBackColor = true;
			this->button_difficulty_normal->Click += gcnew System::EventHandler(this, &form_setting::button_difficulty_normal_Click);
			// 
			// button_difficulty_easy
			// 
			this->button_difficulty_easy->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_difficulty_easy.BackgroundImage")));
			this->button_difficulty_easy->FlatAppearance->BorderSize = 0;
			this->button_difficulty_easy->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_difficulty_easy->ForeColor = System::Drawing::SystemColors::WindowText;
			this->button_difficulty_easy->Location = System::Drawing::Point(0, 0);
			this->button_difficulty_easy->Name = L"button_difficulty_easy";
			this->button_difficulty_easy->Size = System::Drawing::Size(120, 48);
			this->button_difficulty_easy->TabIndex = 15;
			this->button_difficulty_easy->UseVisualStyleBackColor = true;
			this->button_difficulty_easy->Click += gcnew System::EventHandler(this, &form_setting::button_difficulty_easy_Click);
			// 
			// form_setting
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(684, 521);
			this->Controls->Add(this->panel_difficulty);
			this->Controls->Add(this->button_reset);
			this->Controls->Add(this->button_cancel);
			this->Controls->Add(this->button_save);
			this->Controls->Add(this->panel_invincible);
			this->Controls->Add(this->panel_item);
			this->Controls->Add(this->panel_sound);
			this->Controls->Add(this->panel_music_set);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox_title);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"form_setting";
			this->Text = L"設定";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_title))->EndInit();
			this->panel_music_set->ResumeLayout(false);
			this->panel_sound->ResumeLayout(false);
			this->panel_item->ResumeLayout(false);
			this->panel_invincible->ResumeLayout(false);
			this->panel_difficulty->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void button_reset_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_click->Play();
	this->button_invincible_set->Dock = System::Windows::Forms::DockStyle::Right;
	this->button_invincible_set->BackgroundImage = image_onoff[1];
	this->button_item_set->Dock = System::Windows::Forms::DockStyle::Left;
	this->button_item_set->BackgroundImage = image_onoff[0];
	this->button_music_set->Dock = System::Windows::Forms::DockStyle::Left;
	this->button_music_set->BackgroundImage = image_onoff[0];
	this->button_sound_set->Dock = System::Windows::Forms::DockStyle::Left;
	this->button_sound_set->BackgroundImage = image_onoff[0];
	this->button_difficulty_easy->BackgroundImage = image_difficulty[0];
	this->button_difficulty_normal->BackgroundImage = image_difficulty[3];
	this->button_difficulty_hard->BackgroundImage = image_difficulty[5];
	*set_diffculty = 1;
	*set_invincible = false;
	*set_item = true;
	*set_music = true;
	*set_sound = true;
}
private: System::Void button_difficulty_easy_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_click->Play();
	this->button_difficulty_easy->BackgroundImage = image_difficulty[0];
	this->button_difficulty_normal->BackgroundImage = image_difficulty[3];
	this->button_difficulty_hard->BackgroundImage = image_difficulty[5];
	*set_diffculty = 1;
}
private: System::Void button_difficulty_normal_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_click->Play();
	this->button_difficulty_easy->BackgroundImage = image_difficulty[1];
	this->button_difficulty_normal->BackgroundImage = image_difficulty[2];
	this->button_difficulty_hard->BackgroundImage = image_difficulty[5];
	*set_diffculty = 2;
}
private: System::Void button_difficulty_hard_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_click->Play();
	this->button_difficulty_easy->BackgroundImage = image_difficulty[1];
	this->button_difficulty_normal->BackgroundImage = image_difficulty[3];
	this->button_difficulty_hard->BackgroundImage = image_difficulty[4];
	*set_diffculty = 3;

}
private: System::Void button_save_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_click->Play();
	StreamWriter ^fout = gcnew StreamWriter("setting.txt");
	int i = 0;
	while(i<23)
		fout->WriteLine(buffer[i++]);
	fout->WriteLine(*set_music);
	fout->WriteLine(*set_sound);
	fout->WriteLine(*set_item);
	fout->WriteLine(*set_invincible);
	fout->WriteLine(*set_diffculty);
	fout->Close();
	delete fout;
}
private: System::Void panel_music_set_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_click->Play();
	if (this->button_music_set->Dock == System::Windows::Forms::DockStyle::Left)
	{
		this->button_music_set->Dock = System::Windows::Forms::DockStyle::Right;
		this->button_music_set->BackgroundImage = image_onoff[1];
		*set_music = false;
	}
	else
	{
		this->button_music_set->Dock = System::Windows::Forms::DockStyle::Left;
		this->button_music_set->BackgroundImage = image_onoff[0];
		*set_music = true;
	}
}
private: System::Void panel_invincible_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_click->Play();
	if (this->button_invincible_set->Dock == System::Windows::Forms::DockStyle::Left)
	{
		this->button_invincible_set->Dock = System::Windows::Forms::DockStyle::Right;
		this->button_invincible_set->BackgroundImage = image_onoff[1];
		*set_invincible = false;
	}
	else
	{
		this->button_invincible_set->Dock = System::Windows::Forms::DockStyle::Left;
		this->button_invincible_set->BackgroundImage = image_onoff[0];
		*set_invincible = true;
	}
}
private: System::Void panel_item_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_click->Play();
	if (this->button_item_set->Dock == System::Windows::Forms::DockStyle::Left)
	{
		this->button_item_set->Dock = System::Windows::Forms::DockStyle::Right;
		this->button_item_set->BackgroundImage = image_onoff[1];
		*set_item = false;
	}
	else
	{
		this->button_item_set->Dock = System::Windows::Forms::DockStyle::Left;
		this->button_item_set->BackgroundImage = image_onoff[0];
		*set_item = true;
	}

}
private: System::Void panel_sound_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_click->Play();
	if (this->button_sound_set->Dock == System::Windows::Forms::DockStyle::Left)
	{
		this->button_sound_set->Dock = System::Windows::Forms::DockStyle::Right;
		this->button_sound_set->BackgroundImage = image_onoff[1];
		*set_sound = false;
	}
	else
	{
		this->button_sound_set->Dock = System::Windows::Forms::DockStyle::Left;
		this->button_sound_set->BackgroundImage = image_onoff[0];
		*set_sound = true;
	}
}
private: System::Void button_reset_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_mouse_enter->Play();
	this->button_reset->BackgroundImage = image_button[1];
}
private: System::Void button_reset_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
	this->button_reset->BackgroundImage = image_button[0];
}
private: System::Void button_save_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_mouse_enter->Play();
	this->button_save->BackgroundImage = image_button[1];
}
private: System::Void button_save_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
	this->button_save->BackgroundImage = image_button[0];
}
private: System::Void button_cancel_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_mouse_enter->Play();
	this->button_cancel->BackgroundImage = image_button[1];
}
private: System::Void button_cancel_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
	this->button_cancel->BackgroundImage = image_button[0];
}
};
}
