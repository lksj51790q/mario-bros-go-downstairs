#include <cstdlib>
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
	/// form_chart 的摘要
	/// </summary>
	public ref class form_chart : public System::Windows::Forms::Form
	{
	public:
		form_chart(bool^ sound)
		{
			InitializeComponent();

			setting_sound = gcnew bool(*sound);
			//sound
			if (*sound)
			{
				sound_button_mouse_enter = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\mouse_on_button.wav");
				sound_button_click = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\click_button.wav");
			}
			

			String^ buffer = gcnew String(L"");
			StreamReader^ fin = gcnew StreamReader("setting.txt");
			this->label_name->Text = L"";
			this->label_score->Text = L"";
			fin->ReadLine();
			for (; (buffer = fin->ReadLine()) != "score";)
			{
				this->label_name->Text = this->label_name->Text + L"\r\n" + buffer;
			}
			for (; (buffer = fin->ReadLine()) != "setting";)
			{
				this->label_score->Text = this->label_score->Text + L"\r\n" + buffer;
			}
			fin->Close();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~form_chart()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox_chart_title;
	private: System::Windows::Forms::Button^  button_exit;
	private: System::Windows::Forms::Label^  label_name;
	private: System::Windows::Forms::Label^  label_score;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		bool^ setting_sound = nullptr;
		System::Media::SoundPlayer^ sound_button_mouse_enter = nullptr;
		System::Media::SoundPlayer^ sound_button_click = nullptr;
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(form_chart::typeid));
			this->pictureBox_chart_title = (gcnew System::Windows::Forms::PictureBox());
			this->button_exit = (gcnew System::Windows::Forms::Button());
			this->label_name = (gcnew System::Windows::Forms::Label());
			this->label_score = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_chart_title))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox_chart_title
			// 
			this->pictureBox_chart_title->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_chart_title->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_chart_title.Image")));
			this->pictureBox_chart_title->Location = System::Drawing::Point(294, 32);
			this->pictureBox_chart_title->Name = L"pictureBox_chart_title";
			this->pictureBox_chart_title->Size = System::Drawing::Size(150, 48);
			this->pictureBox_chart_title->TabIndex = 0;
			this->pictureBox_chart_title->TabStop = false;
			// 
			// button_exit
			// 
			this->button_exit->BackColor = System::Drawing::Color::Transparent;
			this->button_exit->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button_exit->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->button_exit->FlatAppearance->BorderSize = 0;
			this->button_exit->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->button_exit->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->button_exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_exit->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button_exit->Location = System::Drawing::Point(631, 564);
			this->button_exit->Name = L"button_exit";
			this->button_exit->Size = System::Drawing::Size(90, 44);
			this->button_exit->TabIndex = 1;
			this->button_exit->Text = L"返回";
			this->button_exit->UseVisualStyleBackColor = false;
			this->button_exit->Click += gcnew System::EventHandler(this, &form_chart::button_exit_Click);
			this->button_exit->MouseEnter += gcnew System::EventHandler(this, &form_chart::button_exit_MouseEnter);
			this->button_exit->MouseLeave += gcnew System::EventHandler(this, &form_chart::button_exit_MouseLeave);
			// 
			// label_name
			// 
			this->label_name->Font = (gcnew System::Drawing::Font(L"微軟正黑體 Light", 18));
			this->label_name->Location = System::Drawing::Point(3, 52);
			this->label_name->Name = L"label_name";
			this->label_name->Size = System::Drawing::Size(213, 348);
			this->label_name->TabIndex = 4;
			this->label_name->Text = L"name";
			this->label_name->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_score
			// 
			this->label_score->Font = (gcnew System::Drawing::Font(L"微軟正黑體 Light", 18));
			this->label_score->Location = System::Drawing::Point(222, 52);
			this->label_score->Name = L"label_score";
			this->label_score->Size = System::Drawing::Size(211, 348);
			this->label_score->TabIndex = 5;
			this->label_score->Text = L"score";
			this->label_score->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->label_score);
			this->panel1->Controls->Add(this->label_name);
			this->panel1->Location = System::Drawing::Point(150, 107);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(438, 442);
			this->panel1->TabIndex = 6;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold));
			this->label2->Location = System::Drawing::Point(287, 21);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(78, 31);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Score";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold));
			this->label1->Location = System::Drawing::Point(68, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(84, 31);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Name";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// form_chart
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(722, 609);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button_exit);
			this->Controls->Add(this->pictureBox_chart_title);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"form_chart";
			this->Text = L"排行榜";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_chart_title))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void button_exit_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_mouse_enter->Play();
	this->button_exit->Text = L"返回 →";
	this->button_exit->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
}
private: System::Void button_exit_MouseLeave(System::Object^  sender, System::EventArgs^  e) {

	this->button_exit->Text = L"返回";
	this->button_exit->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
}
private: System::Void button_exit_Click(System::Object^  sender, System::EventArgs^  e) {
	if (*setting_sound)
		sound_button_click->Play();
}
};
}
