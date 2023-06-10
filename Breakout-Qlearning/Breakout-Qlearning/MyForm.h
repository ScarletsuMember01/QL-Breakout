#pragma once

#include "breakout.h"
#include <string>
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include <ostream>
#include <string.h>

namespace BreakoutQlearning {

	bool isNumber(string str) {
		int i = 0;
		for (auto c : str) {
			if (c == '-' && i == 0 && str.size() > 1)
				continue;
			if ((c < '0' || c > '9') && c != '\n')
				return false;
			i++;
		}
		return true;
	}

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	double nbdots = 48;
	double dotspace = 10;

	state st{0,0,0,0,0,0,0};
	state init_state{0,0,0,0,0,0,0};
	vector<double> dots(nbdots,0);
	reward rwd{ -1,-2000,-500, 500,1,2000 };
	qt QTable;
	vector<vector<double>> grid;
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

		qt init_mat(double blocksize, double playersize, double ballxsize, double ballysize, double vxsize, double vysize);

		MyForm(void)
		{
			size = 20;
			side = 15;
			space = 2;
			blocksize = 7;
			win = 0;
			lose = 0;
			count = 0;
			InitializeComponent();
			graphY = pictureBox2->Height - 2;
			QTable = init_mat(3, (size - 4), size, size, 5, 2);
			textBox3->Text = "" + rwd.movemalus;
			textBox4->Text = "" + rwd.blockmalus;
			textBox5->Text = "" + rwd.losemalus;
			textBox6->Text = "" + rwd.winreward;
			textBox7->Text = "" + rwd.blockreward;
			textBox8->Text = "" + rwd.stillreward;
			grid = init_grid(size, blocksize, space);
			isTraining = false;
			init_state = { 7,size / 2 - 1 ,size - 1, size / 2, space + blocksize + 1, 0,1};
			st = init_state;
			timer1->Start();
		}
	private: System::Windows::Forms::Button^ Save;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckedListBox^ checkedListBox1;



	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		double size;
		double side;
		double space;
		double blocksize;
		double graphY;
		bool isTraining;
		int win;
		int lose;
		int count;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Timer^ timer2;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Timer^ timer3;
	private: System::Windows::Forms::TrackBar^ trackBar2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer3 = (gcnew System::Windows::Forms::Timer(this->components));
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->Save = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Control;
			this->pictureBox1->Location = System::Drawing::Point(12, 17);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(300, 315);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(32, 359);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(242, 45);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(290, 359);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(50, 19);
			this->textBox1->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(99, 344);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(90, 12);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Exploration Rate";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(318, 307);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(65, 16);
			this->checkBox1->TabIndex = 4;
			this->checkBox1->Text = L"Training";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// timer1
			// 
			this->timer1->Interval = 1;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// timer3
			// 
			this->timer3->Tick += gcnew System::EventHandler(this, &MyForm::timer3_Tick);
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(419, 359);
			this->trackBar2->Maximum = 5;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(235, 45);
			this->trackBar2->TabIndex = 5;
			this->trackBar2->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar2_Scroll);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(512, 344);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(70, 12);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Interval (ms)";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(660, 359);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(50, 19);
			this->textBox2->TabIndex = 7;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pictureBox2->Location = System::Drawing::Point(320, 40);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(470, 155);
			this->pictureBox2->TabIndex = 8;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox2_Paint);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(316, 220);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 12);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Win/Lose";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(318, 245);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(47, 12);
			this->label4->TabIndex = 10;
			this->label4->Text = L"0/0 (0%)";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(550, 230);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(43, 19);
			this->textBox3->TabIndex = 11;
			this->textBox3->Text = L"-1";
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(550, 255);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(43, 19);
			this->textBox4->TabIndex = 12;
			this->textBox4->Text = L"-200";
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox4_TextChanged);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(550, 280);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(43, 19);
			this->textBox5->TabIndex = 13;
			this->textBox5->Text = L"-1000";
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox5_TextChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(474, 258);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(68, 12);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Block Malus";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(474, 283);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(63, 12);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Lose Malus";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(599, 283);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(59, 12);
			this->label7->TabIndex = 21;
			this->label7->Text = L"Win Bonus";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(599, 258);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(70, 12);
			this->label8->TabIndex = 20;
			this->label8->Text = L"Block Bonus";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(675, 280);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(43, 19);
			this->textBox6->TabIndex = 19;
			this->textBox6->Text = L"1000";
			this->textBox6->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox6_TextChanged);
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(675, 255);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(43, 19);
			this->textBox7->TabIndex = 18;
			this->textBox7->Text = L"100";
			this->textBox7->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox7_TextChanged);
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(675, 230);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(43, 19);
			this->textBox8->TabIndex = 17;
			this->textBox8->Text = L"0";
			this->textBox8->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox8_TextChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(599, 233);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(61, 12);
			this->label9->TabIndex = 16;
			this->label9->Text = L"Still Bonus";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(539, 209);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(84, 12);
			this->label10->TabIndex = 22;
			this->label10->Text = L"Reward Control";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(474, 233);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(66, 12);
			this->label11->TabIndex = 23;
			this->label11->Text = L"Move Malus";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::SystemColors::ControlDark;
			this->label12->Location = System::Drawing::Point(777, 196);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(11, 12);
			this->label12->TabIndex = 24;
			this->label12->Text = L"0";
			// 
			// Save
			// 
			this->Save->Location = System::Drawing::Point(434, 303);
			this->Save->Name = L"Save";
			this->Save->Size = System::Drawing::Size(108, 29);
			this->Save->TabIndex = 25;
			this->Save->Text = L"Save";
			this->Save->UseVisualStyleBackColor = true;
			this->Save->Click += gcnew System::EventHandler(this, &MyForm::Save_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(579, 303);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(108, 29);
			this->button2->TabIndex = 26;
			this->button2->Text = L"Load";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(723, 310);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(55, 11);
			this->checkBox2->TabIndex = 27;
			this->checkBox2->Text = L"Overwrite \?";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Location = System::Drawing::Point(766, 319);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(8, 4);
			this->checkedListBox1->TabIndex = 28;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(827, 406);
			this->Controls->Add(this->checkedListBox1);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->Save);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyBreakout";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void pictureBox2_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e);
	private: System::Void trackBar2_Scroll(System::Object^ sender, System::EventArgs^ e);
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void timer3_Tick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		auto str = msclr::interop::marshal_as<std::string>(textBox3->Text);
		if (str.length() > 0 && isNumber(str))
			rwd.movemalus = std::stod(str);
	}
	private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		auto str = msclr::interop::marshal_as<std::string>(textBox4->Text);
		if (str.length() > 0 && isNumber(str))
			rwd.blockmalus = std::stod(str);
	}
	private: System::Void textBox5_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		auto str = msclr::interop::marshal_as<std::string>(textBox5->Text);
		if (str.length() > 0 && isNumber(str))
			rwd.losemalus = std::stod(str);
	}
	private: System::Void textBox6_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		auto str = msclr::interop::marshal_as<std::string>(textBox6->Text);
		if (str.length() > 0 && isNumber(str))
			rwd.winreward = std::stod(str);
	}
	private: System::Void textBox7_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		auto str = msclr::interop::marshal_as<std::string>(textBox7->Text);
		if (str.length() > 0 && isNumber(str))
			rwd.blockreward = std::stod(str);
	}
	private: System::Void textBox8_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		auto str = msclr::interop::marshal_as<std::string>(textBox8->Text);
		if (str.length() > 0 && isNumber(str))
			rwd.stillreward = std::stod(str);
	}
private: System::Void Save_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!checkBox2->Checked)
		return;
	ofstream myfile("Qtable.txt");
	for (auto block : QTable) {
		for (auto by : block) {
			for (auto bx : by) {
				for (auto vy : bx) {
					for (auto vx : vy) {
						for (auto action : vx) {
							for (auto m : action)
								myfile << m << " ";
							myfile << "\n";
						}
					}
				}
			}
		}
	}
	myfile.close();
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	string my_text;
	string my_tokens;
	ifstream my_file("Qtable.txt");
	if (!my_file)
		return;
	for (auto& block : QTable) {
		for (auto& by : block) {
			for (auto& bx : by) {
				for (auto& vy : bx) {
					for (auto& vx : vy) {
						for (auto& action : vx) {
							getline(my_file, my_text);
							vector<string> result;
							int begin = 0;
							string str;
							for (int i = 0; i < my_text.length(); i++) {
								if (my_text[i] == ' ') {
									result.push_back(str);
									begin = i++;
									str = "";
								}
								if (my_text[i] == '\n')
									continue;
								str.push_back(my_text[i]);
							}
							for (auto i = 0; i < action.size(); i++)
								action[i] = stod(result[i]);
						}
					}
				}
			}
		}
	}
	my_file.close();
	ofstream myfile("QtableTEST.txt");
	for (auto block : QTable) {
		for (auto by : block) {
			for (auto bx : by) {
				for (auto vy : bx) {
					for (auto vx : vy) {
						for (auto action : vx) {
							for (auto m : action)
								myfile << m << " ";
							myfile << "\n";
						}
					}
				}
			}
		}
	}
	myfile.close();
}
};
}
