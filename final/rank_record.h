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
	/// rank_record 的摘要
	/// </summary>
	public ref class rank_record : public System::Windows::Forms::Form
	{
	public:
		int ^place = gcnew int(0);
	private: System::Windows::Forms::Label^  label1;
	public:
		array<String^> ^buffer = gcnew array<String^>(28);
		rank_record(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}
		rank_record(int score)
		{
			InitializeComponent();
			int i=0;
			this->label_text->Text = "恭喜你!!! 獲得了" + score + "分";
			StreamReader^ fin = gcnew StreamReader("setting.txt");
			while (i<28)
			{
				buffer[i++] = fin->ReadLine();
			}
			for (i = 12; i < 23; i++)
			{
				if (buffer[i] == "-")
				{
					this->label_text->Text += "\r\n你這次的名次在第" + ++(*place) + "名";
					break;
				}
				if (score > Int32::Parse(buffer[i]))
				{
					this->label_text->Text += "\r\n你這次的名次在第" + ++(*place) + "名";
					break;
				}	
				else
				{
					(*place)++;
					if (*place == 10)
					{
						this->button_save->Visible = false;
						this->textBox_name->Visible = false;
						this->label1->Visible = false;
						this->label_text->Text += "\r\n你這次的分數未能進入排行榜";
						
						break;
					}
				}
			}
			for (i = 10; i > *place; i--)
			{
				buffer[i + 11] = buffer[i + 10];
				buffer[i] = buffer[i-1];
			}
			buffer[*place+11] = ""+score;
			fin->Close();
			delete fin;
				//
				//TODO:  在此加入建構函式程式碼
				//
		}
	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~rank_record()
		{
			if (components)
			{
				delete components;
				delete place;
			}
		}
	private: System::Windows::Forms::Button^  button_save;
	private: System::Windows::Forms::Button^  button_cancel;
	protected:

	protected:

	private: System::Windows::Forms::Label^  label_text;
	private: System::Windows::Forms::TextBox^  textBox_name;
	private: System::Windows::Forms::Label^  label_warning;



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
			this->button_save = (gcnew System::Windows::Forms::Button());
			this->button_cancel = (gcnew System::Windows::Forms::Button());
			this->label_text = (gcnew System::Windows::Forms::Label());
			this->textBox_name = (gcnew System::Windows::Forms::TextBox());
			this->label_warning = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button_save
			// 
			this->button_save->Location = System::Drawing::Point(120, 201);
			this->button_save->Name = L"button_save";
			this->button_save->Size = System::Drawing::Size(75, 23);
			this->button_save->TabIndex = 2;
			this->button_save->Text = L"儲存";
			this->button_save->UseVisualStyleBackColor = true;
			this->button_save->Click += gcnew System::EventHandler(this, &rank_record::button_save_Click);
			// 
			// button_cancel
			// 
			this->button_cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button_cancel->Location = System::Drawing::Point(242, 201);
			this->button_cancel->Name = L"button_cancel";
			this->button_cancel->Size = System::Drawing::Size(75, 23);
			this->button_cancel->TabIndex = 3;
			this->button_cancel->Text = L"退出";
			this->button_cancel->UseVisualStyleBackColor = true;
			// 
			// label_text
			// 
			this->label_text->AutoSize = true;
			this->label_text->Location = System::Drawing::Point(82, 28);
			this->label_text->Name = L"label_text";
			this->label_text->Size = System::Drawing::Size(33, 12);
			this->label_text->TabIndex = 2;
			this->label_text->Text = L"label1";
			// 
			// textBox_name
			// 
			this->textBox_name->Location = System::Drawing::Point(84, 108);
			this->textBox_name->Name = L"textBox_name";
			this->textBox_name->Size = System::Drawing::Size(100, 22);
			this->textBox_name->TabIndex = 1;
			// 
			// label_warning
			// 
			this->label_warning->AutoSize = true;
			this->label_warning->ForeColor = System::Drawing::Color::Red;
			this->label_warning->Location = System::Drawing::Point(95, 133);
			this->label_warning->Name = L"label_warning";
			this->label_warning->Size = System::Drawing::Size(89, 12);
			this->label_warning->TabIndex = 4;
			this->label_warning->Text = L"請輸入有效名字";
			this->label_warning->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"新細明體", 18));
			this->label1->Location = System::Drawing::Point(19, 106);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 24);
			this->label1->TabIndex = 5;
			this->label1->Text = L"name";
			// 
			// rank_record
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(375, 265);
			this->ControlBox = false;
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label_warning);
			this->Controls->Add(this->textBox_name);
			this->Controls->Add(this->label_text);
			this->Controls->Add(this->button_cancel);
			this->Controls->Add(this->button_save);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"rank_record";
			this->Text = L"紀錄";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_save_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->textBox_name->Text == "")
		{
			this->label_warning->Visible = true;
		}
		else
		{
			buffer[*place] = this->textBox_name->Text;
			StreamWriter^ fout = gcnew StreamWriter("setting.txt");
			int i;
			for (i = 0; i <28; i++)
			{
				fout->WriteLine(buffer[i]);
			}
			fout->Close();
			delete buffer;
			delete fout;
			delete place;
			this->Close();
		}

	}
};
}
