#pragma once
#include "MessageForm.h"
namespace MemoryGame47 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// HeroForm 摘要
	/// </summary>
	public ref class HeroForm : public System::Windows::Forms::Form
	{
	public:
		HeroForm(userlogin * U)
		{
			InitializeComponent();
			this->SetStyle(static_cast<ControlStyles>(ControlStyles::AllPaintingInWmPaint |ControlStyles::DoubleBuffer |ControlStyles::UserPaint), true);
			this->UpdateStyles();

			User=U;
		}

				// Use to decode a PictureBox handle into an index.
		// Input: the handle of a PictureBox.
		// Output: the corresponding index.
		int PtoN(System::Object^  sender)
		{
			if (ReferenceEquals(sender,pictureBox1)) return 0;
			if (ReferenceEquals(sender,pictureBox2)) return 1;
			if (ReferenceEquals(sender,pictureBox3)) return 2;
			if (ReferenceEquals(sender,pictureBox4)) return 3;
		}
	protected:
		~HeroForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected: 
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;

	private:
		userlogin * User;
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(HeroForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(295, 728);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &HeroForm::pictureBox_Click);
			this->pictureBox1->MouseEnter += gcnew System::EventHandler(this, &HeroForm::pictureBox_MouseEnter);
			this->pictureBox1->MouseLeave += gcnew System::EventHandler(this, &HeroForm::pictureBox_MouseLeave);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->Location = System::Drawing::Point(295, 0);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(295, 728);
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &HeroForm::pictureBox_Click);
			this->pictureBox2->MouseEnter += gcnew System::EventHandler(this, &HeroForm::pictureBox_MouseEnter);
			this->pictureBox2->MouseLeave += gcnew System::EventHandler(this, &HeroForm::pictureBox_MouseLeave);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox3->Location = System::Drawing::Point(590, 0);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(295, 728);
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &HeroForm::pictureBox_Click);
			this->pictureBox3->MouseEnter += gcnew System::EventHandler(this, &HeroForm::pictureBox_MouseEnter);
			this->pictureBox3->MouseLeave += gcnew System::EventHandler(this, &HeroForm::pictureBox_MouseLeave);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox4->Location = System::Drawing::Point(885, 0);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(295, 728);
			this->pictureBox4->TabIndex = 3;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &HeroForm::pictureBox_Click);
			this->pictureBox4->MouseEnter += gcnew System::EventHandler(this, &HeroForm::pictureBox_MouseEnter);
			this->pictureBox4->MouseLeave += gcnew System::EventHandler(this, &HeroForm::pictureBox_MouseLeave);
			// 
			// HeroForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1180, 728);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"HeroForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HeroForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void pictureBox_Click(System::Object^  sender, System::EventArgs^  e) {
				 User->sethero(PtoN(sender));
				 User->writefile();
				 this->Close();
			 }
private: System::Void pictureBox_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->BackgroundImage=Image::FromFile(".\\heroes\\bg"+PtoN(sender)+".jpg");
		 }
private: System::Void pictureBox_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->BackgroundImage=Image::FromFile(".\\heroes\\bg.jpg");
		 }
};
}
