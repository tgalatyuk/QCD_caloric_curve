TGraphAsymmErrors* GetLHCUncertainties(TGraphAsymmErrors* grTheory);

void MakeTemperaturePlot(Bool_t bITS3 = kTRUE, Bool_t bNoFuture = kFALSE, Bool_t bNoTheory = kFALSE, Bool_t bNoMeasurements = kFALSE) {
    //
    // plot the relevant temperatures in heavy-ion physics
    //
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    TCanvas * canvTemperature = new TCanvas("canvTemperature","canvTemperature", 800, 600);
    canvTemperature->SetRightMargin(0.04);
    canvTemperature->SetTopMargin(0.04);
    canvTemperature->SetLeftMargin(0.12);
    canvTemperature->SetBottomMargin(0.14);

    TH2D * histLayout = new TH2D("histLayout","temperatures of the fireball; #sqrt{#it{s}_{NN}} (GeV); #it{T} (MeV)",1000,1.0,10000.0,100,0.0,400.);
    histLayout->GetXaxis()->SetTitleSize(0.05);
    histLayout->GetYaxis()->SetTitleSize(0.05);
    histLayout->GetXaxis()->SetLabelSize(0.05);
    histLayout->GetYaxis()->SetLabelSize(0.05);
    histLayout->GetXaxis()->SetTitleOffset(1.20);
    histLayout->GetYaxis()->SetTitleOffset(1.10);
    histLayout->Draw();
    canvTemperature->SetLogx();
    //
    // add parameterisation for chemical freeze-out temp from arXiv:1710.09425v2 (caption figure 3)
    //
    TF1 * fitChemFreezeOut = new TF1("fitChemFreezeOut","158.4/(1 + TMath::Exp(2.6 - TMath::Log(x)/0.45))",2.0,10000.0);
    fitChemFreezeOut->SetLineColor(kBlue);
    fitChemFreezeOut->SetLineWidth(1);
    //
    // TODO: add data points from Anton thermal model (tmu_s.txt) from arXiv:1710.09425v2
    //
    ifstream inFileAnton;
    inFileAnton.open("tmu_s.txt");
    inFileAnton.ignore(10000,'\n');
    Int_t nP = 0;
    Float_t rootS[30], temp[30], muB[30], tempErrLow[30], tempErrUp[30], muBerrLow[30], muBerrUp[30];
    //
    while(!inFileAnton.eof()) {
        inFileAnton >> rootS[nP]
                    >> temp[nP]
                    >> muB[nP]
                    >> tempErrLow[nP]
                    >> tempErrUp[nP]
                    >> muBerrLow[nP]
                    >> muBerrUp[nP];
        nP++;
    }
    TGraphAsymmErrors * grAnton = new TGraphAsymmErrors(nP,rootS,temp,0,0,tempErrLow,tempErrUp);
    grAnton->SetMarkerColor(kBlue);
    grAnton->SetLineColor(kBlue);
    grAnton->SetMarkerSize(1.2);
    grAnton->SetMarkerStyle(20);
     //
    // read-in points from Rapp&Hess after reading it from the plot and add the LHC point (to be done properly)
    //
    // TGraphErrors * grRappHees = new TGraphErrors("xyscan.txt");
    // grRappHees->SetLineWidth(3);
    // grRappHees->SetLineColor(kRed);
    // grRappHees->Draw("lp");

    ifstream inFileTheory;
    inFileTheory.open("TSlope_Theory.txt");
    inFileTheory.ignore(10000,'\n');
    nP = 0;
    while(!inFileTheory.eof()) {
      inFileTheory >> rootS[nP]
		 >> temp[nP]
		 >> tempErrLow[nP]
		 >> tempErrUp[nP];
	nP++;
    }
    TGraphAsymmErrors * grTheoryPublished = new TGraphAsymmErrors(nP-1,rootS,temp,0,0,tempErrLow,tempErrUp);
    TGraphAsymmErrors * grTheory = (TGraphAsymmErrors*)GetLHCUncertainties(grTheoryPublished);
    grTheory->SetMarkerColor(kOrange);
    grTheory->SetLineColor(kOrange);
    grTheory->SetFillColor(kOrange);
    grTheory->SetMarkerSize(1);
    grTheory->SetMarkerStyle(1);
    if(!bNoTheory)
      grTheory->Draw("3");


    ifstream inFileTheoryInitial;
    inFileTheoryInitial.open("TInitial_Theory.txt");
    inFileTheoryInitial.ignore(10000,'\n');
    nP = 0;
    while(!inFileTheoryInitial.eof()) {
      inFileTheoryInitial >> rootS[nP]
		 >> temp[nP]
		 >> tempErrLow[nP]
		 >> tempErrUp[nP];
	nP++;
    }
    TGraphAsymmErrors * grTheoryInitialPublished = new TGraphAsymmErrors(nP-1,rootS,temp,0,0,tempErrLow,tempErrUp);
    TGraphAsymmErrors * grTheoryInitial = (TGraphAsymmErrors*)GetLHCUncertainties(grTheoryInitialPublished);
    grTheoryInitial->SetMarkerColor(kOrange-3);
    grTheoryInitial->SetLineColor(kOrange-3);
    grTheoryInitial->SetFillColor(kOrange-3);
    grTheoryInitial->SetMarkerSize(1);
    grTheoryInitial->SetMarkerStyle(1);
    //grTheoryInitial->Draw("3");
    
    //
    // TODO: add points from Lattice QCD (https://arxiv.org/abs/1812.08235)
    //
    const Double_t temp0c = 156.5; // in MeV
    const Double_t temp0err = 1.5; // in MeV
    const Double_t kappa2 = 0.012;
    const Double_t kappa2err = 0.004;
    const Double_t kappa4 = 0.000;
    const Double_t kappa4err = 0.004;
    //
    Double_t tempLat[100];
    Double_t muBLat[100];
    Double_t sqrtSLat[100];
    Double_t tempLatEyUp[100];
    Double_t tempLatEyDown[100];
    for(Int_t iP = 0; iP < 100; iP++) {
      muBLat[iP] = iP*3.0 + 0.001; // in 3.0MeV steps, calculation is reliable < 300 MeV in muB
      sqrtSLat[iP] = 1/0.288 * (1307.5/muBLat[iP] - 1.0); // sqrt(s) <-> muB correspondence from arXiv:1710.09425
      tempLat[iP] = temp0c * (1 - kappa2 * TMath::Power(muBLat[iP]/temp0c, 2.0) - kappa4 * TMath::Power(muBLat[iP]/temp0c, 4.0) );
      tempLatEyUp[iP] = (temp0c + temp0err) * (1 - (kappa2 - kappa2err) * TMath::Power(muBLat[iP]/temp0c, 2.0) - (kappa4 - kappa4err) * TMath::Power(muBLat[iP]/temp0c, 4.0) );
      tempLatEyUp[iP] = tempLatEyUp[iP] - tempLat[iP];
      tempLatEyDown[iP] = (temp0c - temp0err) * (1 - (kappa2 + kappa2err) * TMath::Power(muBLat[iP]/temp0c, 2.0) - (kappa4 + kappa4err) * TMath::Power(muBLat[iP]/temp0c, 4.0) );
      tempLatEyDown[iP] = tempLat[iP] - tempLatEyDown[iP];
    }
    TGraphAsymmErrors * grLattice = new TGraphAsymmErrors(100, sqrtSLat, tempLat, 0x0, 0x0, tempLatEyDown, tempLatEyUp);
    grLattice->SetLineColor(kGray);
    grLattice->SetMarkerColor(kGray);
    grLattice->SetFillColor(kGray);
    //
    grLattice->Draw("3");
    grAnton->Draw("p");
    fitChemFreezeOut->Draw("same");
    //
    // TODO: add existing points from HADES and NA60 
    //
    ifstream inFileNA60;
    inFileNA60.open("TSlope_NA60.txt");
    inFileNA60.ignore(10000,'\n');
    nP = 0;
    while(!inFileNA60.eof()) {
      inFileNA60 >> rootS[nP]
		 >> temp[nP]
		 >> tempErrLow[nP]
		 >> tempErrUp[nP];
	nP++;
    }
    TGraphAsymmErrors * grNA60 = new TGraphAsymmErrors(nP-1,rootS,temp,0,0,tempErrLow,tempErrUp);
    grNA60->SetMarkerColor(kRed);
    grNA60->SetLineColor(kRed);
    grNA60->SetMarkerSize(1.2);
    grNA60->SetMarkerStyle(20);
    if(!bNoMeasurements)
      grNA60->Draw("p");

    ifstream inFileHADES;
    inFileHADES.open("TSlope_HADES.txt");
    inFileHADES.ignore(10000,'\n');
    nP = 0;
    while(!inFileHADES.eof()) {
      inFileHADES >> rootS[nP]
		 >> temp[nP]
		 >> tempErrLow[nP]
		 >> tempErrUp[nP];
	nP++;
    }
    TGraphAsymmErrors * grHADES = new TGraphAsymmErrors(nP-1,rootS,temp,0,0,tempErrLow,tempErrUp);
    grHADES->SetMarkerColor(kRed);
    grHADES->SetLineColor(kRed);
    grHADES->SetMarkerSize(1.2);
    grHADES->SetMarkerStyle(21);
    if(!bNoMeasurements)
      grHADES->Draw("p");
    
    //
    // TODO: add measurement plans for CBM, NA60+, ALICE, STAR
    //

    ifstream inFileCBM;
    inFileCBM.open("TSlope_CBM.txt");
    inFileCBM.ignore(10000,'\n');
    nP = 0;
    while(!inFileCBM.eof()) {
      inFileCBM >> rootS[nP]
		 >> temp[nP]
		 >> tempErrLow[nP]
		 >> tempErrUp[nP];
	nP++;
    }
    TGraphAsymmErrors * grCBM = new TGraphAsymmErrors(nP-1,rootS,temp,0,0,tempErrLow,tempErrUp);
    grCBM->SetMarkerColor(kRed);
    grCBM->SetLineColor(kRed);
    grCBM->SetMarkerSize(1.2);
    grCBM->SetMarkerStyle(26);
    if(!bNoFuture)
      grCBM->Draw("p");


    ifstream inFileNA60Plus;
    inFileNA60Plus.open("TSlope_NA60Plus.txt");
    inFileNA60Plus.ignore(10000,'\n');
    nP = 0;
    while(!inFileNA60Plus.eof()) {
      inFileNA60Plus >> rootS[nP]
		 >> temp[nP]
		 >> tempErrLow[nP]
		 >> tempErrUp[nP];
	nP++;
    }
    TGraphAsymmErrors * grNA60Plus = new TGraphAsymmErrors(nP-1,rootS,temp,0,0,tempErrLow,tempErrUp);
    grNA60Plus->SetMarkerColor(kRed);
    grNA60Plus->SetLineColor(kRed);
    grNA60Plus->SetMarkerSize(1.2);
    grNA60Plus->SetMarkerStyle(25);
    if(!bNoFuture)
      grNA60Plus->Draw("p");


    ifstream inFileSTAR;
    inFileSTAR.open("TSlope_STAR.txt");
    inFileSTAR.ignore(10000,'\n');
    nP = 0;
    while(!inFileSTAR.eof()) {
      inFileSTAR >> rootS[nP]
		 >> temp[nP]
		 >> tempErrLow[nP]
		 >> tempErrUp[nP];
	nP++;
    }
    TGraphAsymmErrors * grSTAR = new TGraphAsymmErrors(nP-1,rootS,temp,0,0,tempErrLow,tempErrUp);
    grSTAR->SetMarkerColor(kRed);
    grSTAR->SetMarkerSize(1.2);
    grSTAR->SetMarkerStyle(25);
    if(!bNoFuture)
      grSTAR->Draw("p"); // ????? is it on the plot? We don't have the data points...


    ifstream inFileALICE;
    if(bITS3)
      inFileALICE.open("TSlope_ALICE_ITS3.txt");
    else
      inFileALICE.open("TSlope_ALICE.txt");

    inFileALICE.ignore(10000,'\n');
    nP = 0;
    while(!inFileALICE.eof()) {
      inFileALICE >> rootS[nP]
		 >> temp[nP]
		 >> tempErrLow[nP]
		 >> tempErrUp[nP];
	nP++;
    }
    TGraphAsymmErrors * grALICE = new TGraphAsymmErrors(nP-1,rootS,temp,0,0,tempErrLow,tempErrUp);
    grALICE->SetMarkerColor(kRed);
    grALICE->SetLineColor(kRed);
    grALICE->SetMarkerSize(1.2);
    grALICE->SetMarkerStyle(24);
    if(!bNoFuture)
      grALICE->Draw("p");

    //
    // add legends
    //
    TLegend * legHadronisation = new TLegend(0.6, 0.17, 0.9, 0.43, "Hadronisation temperature");
    legHadronisation->SetBorderSize(0);
    legHadronisation->AddEntry(grLattice,"#splitline{Lattice QCD}{PLB 795 (2019) 15}","f");
    legHadronisation->AddEntry(grAnton,"#splitline{SHM fit to experiment}{Nature 561 (2018) 7723}","lp");
    legHadronisation->SetTextSize(0.03);
    legHadronisation->Draw();
    //
    TLegend * legDileptons = NULL;
    if(bNoFuture&&bNoMeasurements&&bNoTheory)
      legDileptons = new TLegend(0.18,0.61,0.49,0.94,"");
    else
      legDileptons = new TLegend(0.18,0.61,0.49,0.94,"Fireball average temperature");
    
    legDileptons->SetBorderSize(0);
    legDileptons->SetFillStyle(0);
    legDileptons->SetNColumns(2);
    if(!bNoMeasurements)
      legDileptons->AddEntry(grNA60, "NA60","lp");
    else
      legDileptons->AddEntry("", "","");

    if(!bNoFuture){
      if(bITS3)
	legDileptons->AddEntry(grALICE, "ALICE ITS3 - 3 nb^{-1} (simulation, stat. only)", "lp");
      else
	legDileptons->AddEntry(grALICE, "ALICE ITS2 - 3 nb^{-1} (simulation, stat. only)", "lp");
    }
    else{
      legDileptons->AddEntry("","","");
    }
    if(!bNoMeasurements)
      legDileptons->AddEntry(grHADES, "HADES","lp");
    else
      legDileptons->AddEntry("", "","");

    if(!bNoFuture){
      legDileptons->AddEntry(grCBM, "CBM (simulation)");
      legDileptons->AddEntry("","","");
      legDileptons->AddEntry(grNA60Plus, "NA60+ (simulation)");
    }
    else{
      legDileptons->AddEntry("","","");
    }
    if(!bNoTheory)
      legDileptons->AddEntry(grTheory,"Model (Rapp #it{et al.})","f");
    
    //legDileptons->AddEntry("","EPJA52 (2016) 131, PLB753 (2016) 586","");

    legDileptons->SetTextSize(0.03);
    legDileptons->Draw();

    TString outFileName = "temperaturePlot";
    if(!bNoFuture)
      outFileName.Append(Form("_ITS%d",bITS3+2));
    else
      outFileName.Append("_noFuture");
    if(bNoTheory)
      outFileName.Append("_noTheory");
    if(bNoMeasurements)
      outFileName.Append("_noMeasurements");

    outFileName.Append(".eps");
    canvTemperature->SaveAs(outFileName.Data());
}

TGraphAsymmErrors* GetLHCUncertainties(TGraphAsymmErrors* grTheory){
  
  if(!grTheory)
    return NULL;

  const Int_t nBinsMax = 10;
  Double_t x[nBinsMax];
  Double_t y[nBinsMax];
  Double_t yErrLow[nBinsMax];
  Double_t yErrUp[nBinsMax];
  Int_t nBins = grTheory->GetN();
  
  if(nBins > nBinsMax){
    Printf("Number of bins %d bigger than maximum allowed bins %d",nBins,nBinsMax);
    return NULL;
  }
  
  for(Int_t iBin = 0; iBin < nBins; iBin++){
    x[iBin]       = grTheory->GetPointX(iBin);
    y[iBin]       = grTheory->GetPointY(iBin);
    yErrLow[iBin] = grTheory->GetErrorYlow(iBin);
    yErrUp[iBin]  = grTheory->GetErrorYhigh(iBin);
    if(iBin==nBins-1){
      yErrLow[iBin] = yErrLow[iBin-1]/y[iBin-1] * y[iBin];
      yErrUp[iBin]  = yErrUp[iBin-1]/y[iBin-1] * y[iBin];
    }
    Printf("Energy = %.2f ==> %.2f - %.2f + %.2f ( + %.2f - %.2f %%)",x[iBin],y[iBin],yErrLow[iBin],yErrUp[iBin],yErrLow[iBin]/y[iBin]*100.,yErrUp[iBin]/y[iBin]*100.);
  }  
  
  TGraphAsymmErrors * grTheoryNew = new TGraphAsymmErrors(nBins,x,y,0,0,yErrLow,yErrUp);

  return grTheoryNew;
}
