#pragma once
#include "MessageForm.h"
namespace MemoryGame47 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Form2 摘要
	/// </summary>
	public ref class Form2 : public System::Windows::Forms::Form
	{
	public:
		Form2(userlogin * U)
		{
			InitializeComponent();
			this->SetStyle(static_cast<ControlStyles>(ControlStyles::AllPaintingInWmPaint |ControlStyles::DoubleBuffer |ControlStyles::UserPaint), true);
			this->UpdateStyles();
			User=U;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form2()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		userlogin * User;

	private: System::Windows::Forms::TextBox^  textBox1;

	private: System::Windows::Forms::TextBox^  textBox2;

	private: System::Windows::Forms::PictureBox^  pictureBox1;
			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form2::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(142)), 
				static_cast<System::Int32>(static_cast<System::Byte>(58)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"微软雅黑", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textBox1->ForeColor = System::Drawing::Color::Black;
			this->textBox1->Location = System::Drawing::Point(243, 492);
			this->textBox1->MaxLength = 20;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(178, 28);
			this->textBox1->TabIndex = 1;
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(142)), 
				static_cast<System::Int32>(static_cast<System::Byte>(58)));
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"微软雅黑", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textBox2->ForeColor = System::Drawing::Color::Black;
			this->textBox2->Location = System::Drawing::Point(243, 533);
			this->textBox2->MaxLength = 20;
			this->textBox2->Name = L"textBox2";
			this->textBox2->PasswordChar = '*';
			this->textBox2->Size = System::Drawing::Size(178, 28);
			this->textBox2->TabIndex = 3;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Location = System::Drawing::Point(190, 590);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(135, 78);
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form2::pictureBox1_Click);
			// 
			// Form2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(520, 712);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form2";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"User Login";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			 String ^ Username=textBox1->Text;
				 String ^ Password=textBox2->Text;
				 char * username=(char*)Marshal::StringToHGlobalAnsi(Username).ToPointer();
				 char * password=(char*)Marshal::StringToHGlobalAnsi(Password).ToPointer();
				 if (Username=="")
				 {
					 MessageForm ^ MF=gcnew MessageForm("Please input a valid username!","Error",false,User);
					 MF->ShowDialog();
					 return;
				 }
				 int check=User->readfile(username,password);
				 if (check==-1)
				 {
					 // Create new user profile.
					 for (int i=0;i<5;i++) // Here sets the initial number of normal kinds.
						 User->setpk(i,true);
					 for (int i=0;i<6;i++) // Here sets the initial number of special kinds.
						 User->setpsp(i,true);
					 String ^ M="Welcome "+Username+"!\r\n";
					 M+="This is your first time to the dungeon.\r\n";
					 M+="We have marked down your name on our list.\r\n";
					 M+="Hope you find your memory back!";
					 MessageForm ^ MF=gcnew MessageForm(M,"New Finder",false,User);
					 MF->ShowDialog();
				 }
				 else
				 {
					 if (check==-2)
					 {
						String ^ M="Password wrong!\r\n";
						M+="You are not allow to get into the dungeon!";
					    MessageForm ^ MF=gcnew MessageForm(M,"Error",false,User);
					    MF->ShowDialog();
						return;
					 }
					 else
					 {
						 String ^ M="Welcome back to the dungeon, "+Username+"!";
					     MessageForm ^ MF=gcnew MessageForm(M,"Welcome back",false,User);
					     MF->ShowDialog();
					 }
				 }
				 Marshal::FreeHGlobal((IntPtr)username);
				 Marshal::FreeHGlobal((IntPtr)password);
				 this->Close();
		 }
};
}
