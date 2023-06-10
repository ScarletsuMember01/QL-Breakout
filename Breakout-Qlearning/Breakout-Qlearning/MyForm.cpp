#include "MyForm.h"

using namespace System;
using namespace std;
using namespace System::Windows::Forms;
int consecutives = 0;

[STAThread]

// Init QTable
qt BreakoutQlearning::MyForm::init_mat(double blocksize, double playersize, double ballxsize, double ballysize, double vxsize, double vysize) {
	qt QT;
	for (auto block = 0; block < pow(2,blocksize); block++) {
		vector<vector<vector<vector<vector<vector<double>>>>>> Qtblock;
		for (auto i = 0; i < playersize; i++) {
			vector<vector<vector<vector<vector<double>>>>> Qtby;
			for (auto by = 0; by < ballysize; by++) {
				vector<vector<vector<vector<double>>>> Qtbx;
				for (auto bx = 0; bx < ballxsize; bx++) {
					vector<vector<vector<double>>> Qtvy;
					for (auto vy = 0; vy < vysize; vy++) {
						vector<vector<double>> Qtvx;
						for (auto vx = 0; vx < vxsize; vx++) {
							vector<double> action;
							for (auto j = 0; j < 3; j++) {
								action.push_back(0);
							}
							Qtvx.push_back(action);
						}
						Qtvy.push_back(Qtvx);
					}
					Qtbx.push_back(Qtvy);
				}
				Qtby.push_back(Qtbx);
			}
			Qtblock.push_back(Qtby);
		}
		QT.push_back(Qtblock);
	}

	return QT;
}

// Game PictureBox
System::Void BreakoutQlearning::MyForm::pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	

	//Draw Blocks
	for (auto i = space; i < blocksize + space; i++)
	{
		System::Drawing::SolidBrush^ myBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Yellow);
		System::Drawing::SolidBrush^ myBrush2 = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);

		for (auto j = 0; j < size; j++) {
			
			if (grid[i][j] == 2)
				e->Graphics->FillRectangle(myBrush2, System::Drawing::Rectangle(j * side, i * side, side, side));
			else if (grid[i][j] != 0)
				e->Graphics->FillRectangle(myBrush, System::Drawing::Rectangle(j * side, i * side, side, side));
			
			//if (grid[i][j] != 0)
			//	e->Graphics->FillRectangle(myBrush, System::Drawing::Rectangle(j * side, i * side, side, side));
		}
	}

	int posy = st.py + 1; //below player
	double vx = st.vx + 2;
	double vy = st.vy;
	if (st.vy == -1)
		vy = 0;
	//Color best action for player
	for (auto j = 0; j < size; j++) {
		int action;
		double val = 0;
		if (j >= size - 4)
			action = 0;
		else {
			action = max_element(QTable[st.block][j][st.by][st.bx][vy][vx].begin(), QTable[st.block][j][st.by][st.bx][vy][vx].end()) - QTable[st.block][j][st.by][st.bx][vy][vx].begin();
			val = QTable[st.block][j][st.by][st.bx][vy][vx][action];
			if (val < 0)
				val = 0;
			val = val / (rwd.winreward + 2 * rwd.blockreward);
			if (val >= 1)
				val = 1;
		}
		PointF p1, p2, p3;
		int r = 0;
		int g = 0;
		int b = 0;
		int margin = 5;
		System::Drawing::SolidBrush^ brush;
		switch (action)
		{
		case 0:
			r = 100 * val + 150;
			if (val > 0.8) {
				b = 150 * val;
				g = 150 * val;
			}
			p1 = PointF((j + 1) * side - margin, posy * side + margin);
			p2 = PointF(j * side + margin, posy * side + side / 2);
			p3 = PointF((j + 1) * side - margin, (posy + 1 ) * side - margin);
			break;
		case 1:
			g = 100 * val + 150;
			if (val > 0.8) {
				b = 150 * val;
				r = 150 * val;
			}
			p1 = PointF(j * side + margin, posy * side + margin);
			p2 = PointF((j + 1) * side - margin, posy * side + side / 2);
			p3 = PointF(j * side + margin, (posy+1)*side - margin);
			break;
		case 2:
			b = 100 * val + 150;
			if (val > 0.8) {
				r = 150 * val;
				g = 150 * val;
			}
			p1 = PointF(j * side + margin, (posy + 1) * side - margin);
			p2 = PointF((j + 1) * side - margin, posy * side + margin);
			p3 = PointF(j * side + margin, posy * side + margin);
			break;
		}
		brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(255, r, g, b));
		e->Graphics->FillRectangle(brush, System::Drawing::Rectangle(j * side, posy * side, side, side));
		Pen^ blackPen = gcnew Pen(Color::Black, 1.0f);
		e->Graphics->DrawLine(blackPen, p1, p2);
		if (action == 2)
			p2 = PointF((j + 1) * side - margin, (posy+1)*side - margin);
		e->Graphics->DrawLine(blackPen, p2, p3);
	}


	System::Drawing::SolidBrush^ brushBall = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Purple);
	System::Drawing::SolidBrush^ brushPlayer = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);

	e->Graphics->FillEllipse(brushBall, System::Drawing::Rectangle(st.bx * side, st.by * side, side, side));
	e->Graphics->FillRectangle(brushPlayer, System::Drawing::Rectangle(st.px * side, st.py * side, side * 5, side));
}

// Graph PictureBox
System::Void BreakoutQlearning::MyForm::pictureBox2_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	Pen^ blackPen = gcnew Pen(Color::Black, 1.0f);
	PointF lastp = PointF(0, graphY- dots[0]);
	int i = 0;
	for (auto i = 0; i < dots.size(); i++) {
		PointF pt = PointF(i * dotspace, graphY - dots[i]);
		e->Graphics->DrawLine(blackPen, lastp, pt);
		lastp = pt;
	}
}

// TrackBar for ExplorationRate
System::Void BreakoutQlearning::MyForm::trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
	double explo_str = trackBar1->Value * 0.1;
	textBox1->Text = explo_str.ToString();
}

// TrackBar for Interval for each tick
System::Void BreakoutQlearning::MyForm::trackBar2_Scroll(System::Object^ sender, System::EventArgs^ e) {
	double interval = trackBar2->Value * 100 + 1;
	timer3->Interval = interval;
	textBox2->Text = interval.ToString();
}

// CheckBox to Undo/Start Training
System::Void BreakoutQlearning::MyForm::checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	isTraining = !isTraining;
	if (!isTraining)
		timer3->Start();
	else
		timer3->Stop();
}

// Timer for Fast Training
System::Void BreakoutQlearning::MyForm::timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	if (isTraining)
	{
		int i = 0;
		int finished = 0;
		while (finished == 0 && i < 500) {
			finished = train(QTable, st, grid, trackBar1->Value * 0.1, rwd, i);
			if (finished == 1)
			{
				win++;
				count++;
			}
			else if (finished == -1)
				lose++;
			i++;
		}
		if ((win + lose) % 100 == 0)
		{
			dots.erase(dots.begin());
			double c = count;
			dots.push_back(c);
			count = 0;
			label12->Text = "" + c;
			pictureBox2->Refresh();
		}

		double val = floor(((double)win / (double)(win + lose)) * 10000) / 100;
		label4->Text = win + "/" + lose + " (" + val + "%)";

		// RESET randomly when game lost/won or after 1000 iteration random
		grid = init_grid(size, blocksize, space);
		st.block = 7;
		st.vy = 1;
		st.vx = (int)(((float)rand() / (RAND_MAX + 1)) * 5) - 2;
		st.bx = (int)(((float)rand() / (RAND_MAX + 1)) * (size - 5)) + 2;
		st.by = (int)(((float)rand() / (RAND_MAX + 1)) * 3) + 7;
		st.px = (int)(((float)rand() / (RAND_MAX + 1)) * (size - 4));
	}
}

// Timer for Slow Training
System::Void BreakoutQlearning::MyForm::timer3_Tick(System::Object^ sender, System::EventArgs^ e) {
	int finished = train(QTable, st, grid, trackBar1->Value * 0.1, rwd, consecutives++);
	if (finished != 0)
	{
		if (finished == 1)
		{
			win++;
			count++;
		}
		else if (finished == -1)
			lose++;
		if ((win + lose) % 100 == 0)
		{
			dots.erase(dots.begin());
			double c = count;
			dots.push_back(c);
			count = 0;
			label12->Text = "" + c;
			pictureBox2->Refresh();
		}

		double val = floor(((double)win / (double)(win + lose)) * 10000) / 100;
		label4->Text = win + "/" + lose + " (" + val + "%)";

		//RESET
		grid = init_grid(size, blocksize, space);
		st.block = 7;
		st.vy = 1;
		st.vx = (int)(((float)rand() / (RAND_MAX + 1)) * 5) - 2;
		st.bx = (int)(((float)rand() / (RAND_MAX + 1)) * (size - 5)) + 2;
		st.by = (int)(((float)rand() / (RAND_MAX + 1)) * 3) + 7;
		st.px = (int)(((float)rand() / (RAND_MAX + 1)) * (size - 4));
		consecutives = 0;
		cout << "player " << st.px << " ballCoords(" << st.bx << ";"  << st.by << ") velocity(" << st.vx << ";" << st.vy << ')' << endl;
	}
	pictureBox1->Refresh();

}

void main()
{

    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

    BreakoutQlearning::MyForm form;

    Application::Run(% form);

}