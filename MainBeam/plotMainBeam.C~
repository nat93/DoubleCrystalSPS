int plotMainBeam()
{
	const int nn = 1000;
	double x, xp, y, yp;

	double nSigma	= 4.0;
	double ax 	= 1.51002;
	double ay 	= -0.972591;
	double bx 	= 76.1635;		// [m]
	double by 	= 45.4907;		// [m]
	double gx 	= (1.0 + ax*ax)/bx;
	double gy 	= (1.0 + ay*ay)/by;
	double eps 	= nSigma*nSigma*5.0e-9; // [m*rad]
	double xmin	= (-1.0)*TMath::Sqrt(eps*bx);
	double xmax	= TMath::Sqrt(eps*bx);
	double ymin	= (-1.0)*TMath::Sqrt(eps*by);
	double ymax	= TMath::Sqrt(eps*by);
	double dx	= (xmax - xmin)/(nn-1);
	double dy	= (ymax - ymin)/(nn-1);
	double xWidth 	= 0.1; 			// [mm]

	double xpmin	= (-1)*TMath::Sqrt(eps*gx);
	double xpmax	= TMath::Sqrt(eps*gx);
	double ypmin	= (-1)*TMath::Sqrt(eps*gy);
	double ypmax	= TMath::Sqrt(eps*gy);

	TGraph* grXneg = new TGraph();
	grXneg->SetName("grXneg");
	TGraph* grXpos = new TGraph();
	grXpos->SetName("grXpos");
	TGraph* grYneg = new TGraph();
	grYneg->SetName("grYneg");
	TGraph* grYpos = new TGraph();
	grYpos->SetName("grYpos");

	for(int i = 0; i < nn; i++)
	{
		x = xmin + dx*i;
		y = ymin + dy*i;

		xp = getPrime(x,ax,bx,gx,eps,-1);
		yp = getPrime(y,ay,by,gy,eps,-1);
		grXneg->SetPoint(grXneg->GetN(),x*1e3,xp*1e6);
		grYneg->SetPoint(grYneg->GetN(),y*1e3,yp*1e6);

		xp = getPrime(x,ax,bx,gx,eps,+1);
		yp = getPrime(y,ay,by,gy,eps,+1);
		grXpos->SetPoint(grXpos->GetN(),x*1e3,xp*1e6);
		grYpos->SetPoint(grYpos->GetN(),y*1e3,yp*1e6);
	}

	TCanvas* c1 = new TCanvas("c1","c1 XXp",1000,1000);
	c1->cd();
	gPad->SetGrid();
	grXneg->SetLineColor(kBlue);
	grXpos->SetLineColor(kRed);
	grXneg->GetXaxis()->SetLimits(1.2*xmin*1e3,1.2*xmax*1e3);
	grXneg->SetMinimum(1.2*xpmin*1e6);
	grXneg->SetMaximum(1.2*xpmax*1e6);
	grXneg->Draw("AL");
	grXpos->Draw("L SAME");

        grXneg->GetYaxis()->SetTitle("X' [#murad]");
        grXneg->GetXaxis()->SetTitle("X [mm]");
        grXneg->GetXaxis()->CenterTitle();
        grXneg->GetYaxis()->CenterTitle();

	TLine* line1 = new TLine(xmin*1e3,ax*TMath::Sqrt(eps/bx)*1e6,xmin*1e3,0);
	line1->SetLineColor(kBlack);
	line1->SetLineWidth(2);
	line1->SetLineStyle(9);
	line1->Draw();

	TLine* line2 = new TLine(xmin*1e3 + xWidth,getPrime(xmin + xWidth*1e-3,ax,bx,gx,eps,+1)*1e6,xmin*1e3 + xWidth,0);
	line2->SetLineColor(kBlack);
	line2->SetLineWidth(2);
	line2->SetLineStyle(9);
	line2->Draw();

	cout<<"--> Xp size: "<<getPrime(xmin + xWidth*1e-3,ax,bx,gx,eps,+1)*1e6 - getPrime(xmin + xWidth*1e-3,ax,bx,gx,eps,-1)*1e6<<" [urad]"<<endl;

	TCanvas* c2 = new TCanvas("c2","c2 YYp",1000,1000);
	c2->cd();
	gPad->SetGrid();
	grYneg->SetLineColor(kBlue);
	grYpos->SetLineColor(kRed);
	grYneg->GetXaxis()->SetLimits(1.2*ymin*1e3,1.2*ymax*1e3);
	grYneg->SetMinimum(1.2*ypmin*1e6);
	grYneg->SetMaximum(1.2*ypmax*1e6);
	grYneg->Draw("AL");
	grYpos->Draw("L SAME");

        grYneg->GetYaxis()->SetTitle("Y' [#murad]");
        grYneg->GetXaxis()->SetTitle("Y [mm]");
        grYneg->GetXaxis()->CenterTitle();
        grYneg->GetYaxis()->CenterTitle();


	cout<<endl<<endl<<"--> For the Simulation <--"<<endl;
	cout<<"--> dX = "<<xWidth<<" [mm]"<<endl;
	cout<<"--> SigmaXp = "<<0.5*(getPrime(xmin + xWidth*1e-3,ax,bx,gx,eps,+1)*1e6 - getPrime(xmin + xWidth*1e-3,ax,bx,gx,eps,-1)*1e6)/nSigma<<" [urad]"<<endl;
	cout<<"--> SigmaY = "<<(ymax*1e3)/nSigma<<" [mm]"<<endl;
	cout<<"--> SigmaYp = "<<(ypmax*1e6)/nSigma<<" [urad]"<<endl;
	cout<<"--> SigmaX = "<<(xmax*1e3)/nSigma<<" [mm]"<<endl;
	cout<<"--> SigmaXp = "<<(xpmax*1e6)/nSigma<<" [urad]"<<endl;

/**/

	return 0;
}

double getPrime(double X, double a, double b, double g, double eps, int sign)
{
	double Y = 0;
	double D = TMath::Power(2*a*X/b,2) - 4*(g*X*X-eps)/b;
	if(D >= 0)
	{
		Y = 0.5*(-2*a*X/b + sign*TMath::Sqrt(D));
	}
	else
	{
		cout<<endl<<"--> ERROR:: Discriminant (D) < 0 <--"<<endl;
		assert(0);
	}
	return Y;
}
