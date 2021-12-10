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
	/// ShopForm 摘要
	/// </summary>
	public ref class ShopForm : public System::Windows::Forms::Form
	{
	public:
		ShopForm(userlogin * U)
		{
			InitializeComponent();
			this->SetStyle(static_cast<ControlStyles>(ControlStyles::AllPaintingInWmPaint |ControlStyles::DoubleBuffer |ControlStyles::UserPaint), true);
			this->UpdateStyles();
			User=U;
			label1->Text=""+User->getcredit();
			x=0;
			cycle=1;
			count=10;
			gift=false;
		}

	protected:
		~ShopForm()
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
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::PictureBox^  pictureBox9;
	private: System::Windows::Forms::PictureBox^  pictureBox10;
	private: System::Windows::Forms::PictureBox^  pictureBox11;

	private:
		userlogin * User;
		PictureBox ^ PB;
		int x,cycle;
		int count;
		bool result;
		String ^ ImagePath;
		bool gift;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label3;
	private: System::ComponentModel::IContainer^  components;




#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ShopForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox11))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Location = System::Drawing::Point(54, 90);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(64, 64);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &ShopForm::pictureBox_Click);
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ShopForm::pictureBox_Paint);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox2->Location = System::Drawing::Point(134, 90);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(64, 64);
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &ShopForm::pictureBox_Click);
			this->pictureBox2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ShopForm::pictureBox_Paint);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox3->Location = System::Drawing::Point(214, 90);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(64, 64);
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &ShopForm::pictureBox_Click);
			this->pictureBox3->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ShopForm::pictureBox_Paint);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox4->Location = System::Drawing::Point(295, 90);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(64, 64);
			this->pictureBox4->TabIndex = 3;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &ShopForm::pictureBox_Click);
			this->pictureBox4->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ShopForm::pictureBox_Paint);
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox5->Location = System::Drawing::Point(373, 90);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(64, 64);
			this->pictureBox5->TabIndex = 4;
			this->pictureBox5->TabStop = false;
			this->pictureBox5->Click += gcnew System::EventHandler(this, &ShopForm::pictureBox_Click);
			this->pictureBox5->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ShopForm::pictureBox_Paint);
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox6->Location = System::Drawing::Point(54, 166);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(64, 64);
			this->pictureBox6->TabIndex = 5;
			this->pictureBox6->TabStop = false;
			this->pictureBox6->Click += gcnew System::EventHandler(this, &ShopForm::pictureBox_Click);
			this->pictureBox6->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ShopForm::pictureBox_Paint);
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox7->Location = System::Drawing::Point(134, 166);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(64, 64);
			this->pictureBox7->TabIndex = 6;
			this->pictureBox7->TabStop = false;
			this->pictureBox7->Click += gcnew System::EventHandler(this, &ShopForm::pictureBox_Click);
			this->pictureBox7->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ShopForm::pictureBox_Paint);
			// 
			// pictureBox8
			// 
			this->pictureBox8->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox8->Location = System::Drawing::Point(214, 166);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(64, 64);
			this->pictureBox8->TabIndex = 7;
			this->pictureBox8->TabStop = false;
			this->pictureBox8->Click += gcnew System::EventHandler(this, &ShopForm::pictureBox_Click);
			this->pictureBox8->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ShopForm::pictureBox_Paint);
			// 
			// pictureBox9
			// 
			this->pictureBox9->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox9->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox9->Location = System::Drawing::Point(295, 166);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(64, 64);
			this->pictureBox9->TabIndex = 8;
			this->pictureBox9->TabStop = false;
			this->pictureBox9->Click += gcnew System::EventHandler(this, &ShopForm::pictureBox_Click);
			this->pictureBox9->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ShopForm::pictureBox_Paint);
			// 
			// pictureBox10
			// 
			this->pictureBox10->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox10->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox10->Location = System::Drawing::Point(373, 166);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(64, 64);
			this->pictureBox10->TabIndex = 9;
			this->pictureBox10->TabStop = false;
			this->pictureBox10->Click += gcnew System::EventHandler(this, &ShopForm::pictureBox_Click);
			this->pictureBox10->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ShopForm::pictureBox_Paint);
			// 
			// pictureBox11
			// 
			this->pictureBox11->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox11->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox11.BackgroundImage")));
			this->pictureBox11->Location = System::Drawing::Point(164, 564);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(167, 95);
			this->pictureBox11->TabIndex = 10;
			this->pictureBox11->TabStop = false;
			this->pictureBox11->Click += gcnew System::EventHandler(this, &ShopForm::pictureBox11_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"微软雅黑", 10.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->ForeColor = System::Drawing::Color::Black;
			this->label1->Location = System::Drawing::Point(283, 352);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(18, 19);
			this->label1->TabIndex = 12;
			this->label1->Text = L"0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"微软雅黑", 10.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label2->ForeColor = System::Drawing::Color::Black;
			this->label2->Location = System::Drawing::Point(201, 374);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(36, 19);
			this->label2->TabIndex = 13;
			this->label2->Text = L"10C";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &ShopForm::timer1_Tick);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"微软雅黑", 10.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label3->Location = System::Drawing::Point(49, 416);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(236, 19);
			this->label3->TabIndex = 14;
			this->label3->Text = L"Have a try to find your memory!";
			// 
			// ShopForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(493, 663);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox11);
			this->Controls->Add(this->pictureBox10);
			this->Controls->Add(this->pictureBox9);
			this->Controls->Add(this->pictureBox8);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"ShopForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Shop";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox11))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void pictureBox11_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (timer1->Enabled==false)
			 {
				if (gift)
				{
					String ^ M="Thanks for drawing ten times!\r\n";
					M+="You get a free gift!\r\n";
					M+="Please receive it!";
					MessageForm ^ MF=gcnew MessageForm(M,"Wow",true,User);
					MF->ShowDialog();
				}
				this->Close();
			 }
		 }
private: System::Void pictureBox_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((timer1->Enabled==false)&&(User->getcredit()>=count))
			 {
				PB=safe_cast<PictureBox^>(sender);
				PB->Enabled=false;
				x=0;
				cycle=1;
				int pass=count;
				count--;
				label2->Text=""+count+"C";
				// Dealing with purchase action.
				result=User->randompk(&pass);
				ImagePath=".\\cards\\"+pass+".gif";
				if (result==true)
					label1->Text=""+User->getcredit();
				else
					label1->Text=""+(User->getcredit()-1);

				label3->Text="Finding...";
				timer1->Interval=10;
				timer1->Enabled=true;
			 }
			 else if (User->getcredit()<count)
			 {
				 label3->Text="Not enough credit.";
			 }
		 }
private: System::Void pictureBox_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				Bitmap ^ Bp=gcnew Bitmap(".\\cards\\p.png");
				int w=pictureBox1->Size.Width;
				if (timer1->Enabled==false)
				{
					Drawing::Rectangle Area=Drawing::Rectangle(x,0,w-2*x,w);
					e->Graphics->DrawImage(Bp,Area);
					return;
				}
				 if (x<w/2)
				 {
					Drawing::Rectangle Area=Drawing::Rectangle(x,0,w-2*x,w);
					e->Graphics->DrawImage(Bp,Area);
					x+=16;
				 }
				 else if (x<w)
				 {
					 if (cycle==7)
					 {
						Bp=gcnew Bitmap(ImagePath);
						Drawing::Rectangle Area=Drawing::Rectangle(w-x,0,w-2*(w-x),w);
						e->Graphics->DrawImage(Bp,Area);
						x+=16;
					 }
					 else
					 {
						 Drawing::Rectangle Area=Drawing::Rectangle(w-x,0,w-2*(w-x),w);
						 e->Graphics->DrawImage(Bp,Area);
						 x+=16;
					 }
			     }
				 else
				 {
					 if (cycle==7)
					 {
						Bp=gcnew Bitmap(ImagePath);
						Drawing::Rectangle Area=Drawing::Rectangle(0,0,w,w);
						e->Graphics->DrawImage(Bp,Area);
						timer1->Enabled=false;
						if (result==true)
						{
							label3->Text="You find part of your memory!";
						}
						else
						{
							label3->Text="Sorry, not lucky enough.\r\n1 credit returns to you.";
							label1->Text=""+User->getcredit();
						}
						if (count==0)
						{
							gift=true;
						}
					 }
					 else
					 {
						Drawing::Rectangle Area=Drawing::Rectangle(0,0,w,w);
						e->Graphics->DrawImage(Bp,Area);
						cycle++;
						x=0;
						timer1->Interval+=10;
					 }
				 }
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 PB->Invalidate();
		 }
};
}
