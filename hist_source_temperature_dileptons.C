// ==============================================================
// QCD caloric curve
// Date:    2015-Apr-27
// Update:  2018-May-01
// Author:  Tetyana Galatyuk
//
// Cite as:
// T. Galatyuk, Quark Matter 2018, https:indico.cern.ch/event/656452/contributions/2899684/
// sqrt s > 6 GeV: R. Rapp and H.v. Hess, Phys.Lett.B 753 (2016) 586-590
// sqrt s < 6 GeV: T. Galatyuk et al., Eur. Phys. J. A52 (5) (2016) 131
// [NA60], H.J.Specht, AIP Conf.Proc. 1322 (2010) 1, 1-10
// [HADES], Nature Phys. 15 (2019) 10, 1040-1045
// ==============================================================
{
    gROOT->Reset();
    #include "Riostream.h"
    #include "TColor.h"

    gStyle->SetEndErrorSize(3);

    // ----------------------------------------------------------
    gStyle->SetPaperSize(28, 28);
    gStyle->SetOptStat(0);
    TH2F *h1 = new TH2F("h1", "", 249, 1, 250, 390, 0, 390);
    h1->GetXaxis()->SetTitle("Collision Energy #sqrt{s_{NN}} [GeV]");
    h1->GetXaxis()->SetTitleFont(42);
    h1->GetXaxis()->SetTitleColor(1);
    h1->GetXaxis()->SetTitleOffset(1.1);
    h1->GetYaxis()->SetNdivisions(510);
    h1->GetXaxis()->SetTitleSize(0.06);
    h1->GetXaxis()->SetLabelFont(42);
    h1->GetXaxis()->SetLabelSize(0.06);
    h1->GetXaxis()->SetNdivisions(510);
    h1->GetYaxis()->SetTitle("Temperature [MeV]");
    h1->GetYaxis()->SetTitleFont(42);
    h1->GetYaxis()->SetTitleOffset(0.8);
    h1->GetYaxis()->SetTitleSize(0.06);
    h1->GetYaxis()->SetLabelFont(42);
    h1->GetYaxis()->SetLabelSize(0.05);
    h1->GetYaxis()->SetRangeUser(50.,390.);
    h1->GetZaxis()->SetLabelFont(42);
    h1->GetZaxis()->SetLabelSize(0.06);
    h1->SetTitle();
    //--------------------------------------


    //--------------------------------------
    // NA60
    //--------------------------------------
    Double_t na60_mub[] = {17.3};
    Double_t na60_t[] = {205};
    TGraphAsymmErrors *gr_na60  = new TGraphAsymmErrors(1, na60_mub, na60_t);
    gr_na60->SetPointError(0, 0, 0, 12, 12);
    gr_na60->SetMarkerColor(1);
    gr_na60->SetLineColor(1);
    gr_na60->SetLineWidth(3);
    gr_na60->SetMarkerSize(3);
    gr_na60->SetMarkerStyle(22);


    //--------------------------------------
    // HADES
    //--------------------------------------
    Double_t hades_mub[] = {2.42};
    Double_t hades_t[] = {72};
    TGraphAsymmErrors *gr_hades  = new TGraphAsymmErrors(1, hades_mub, hades_t);
    gr_hades->SetPointError(0, 0, 0, 2, 2);
    gr_hades->SetMarkerColor(1);
    gr_hades->SetLineColor(1);
    gr_hades->SetLineWidth(3);
    gr_hades->SetMarkerSize(2.6);
    gr_hades->SetMarkerStyle(21);


    //--------------------------------------
    // R. Rapp& H.v. Hess PLB
    //--------------------------------------
    Double_t rapps_mub[] = {6.27, 8.77, 19.6, 62.4, 200};
    Double_t rapps_t[] = {163.0, 169.8, 189.4, 217.9, 255.0};
    TGraphAsymmErrors *gr_rapps  = new TGraphAsymmErrors(5, rapps_mub, rapps_t);
    gr_rapps->SetPointError(0, 0, 0, 4.0, 5.9);
    gr_rapps->SetPointError(1, 0, 0, 4.4, 7.2);
    gr_rapps->SetPointError(2, 0, 0, 6.7, 11.8);
    gr_rapps->SetPointError(3, 0, 0, 10.4, 15.3);
    gr_rapps->SetPointError(4, 0, 0, 12.5, 16.9);
    gr_rapps->SetMarkerColor(kPink-1);
    gr_rapps->SetLineColor(kPink-1);
    gr_rapps->SetLineWidth(1);
    gr_rapps->SetMarkerSize(1.8);
    gr_rapps->SetMarkerStyle(33);


    //--------------------------------------
    // R. Rapp& H.v. Hess PLB
    //--------------------------------------
    Double_t rappi_mub[] = {6.27, 8.77, 19.6, 62.4, 200};
    Double_t rappi_t[]   = {185,   198,  238,  291, 363};
    TGraphAsymmErrors *gr_rappi  = new TGraphAsymmErrors(5, rappi_mub, rappi_t);
    gr_rappi->SetPointError(0, 0, 0, 8,  12);
    gr_rappi->SetPointError(1, 0, 0, 10, 15);
    gr_rappi->SetPointError(2, 0, 0, 15, 24);
    gr_rappi->SetPointError(3, 0, 0, 21, 33);
    gr_rappi->SetPointError(4, 0, 0, 28, 43);
    gr_rappi->SetMarkerColor(kMagenta+2);
    gr_rappi->SetLineColor(kMagenta+2);
    gr_rappi->SetLineWidth(1);
    gr_rappi->SetMarkerSize(1.5);
    gr_rappi->SetMarkerStyle(23);
    TGraphAsymmErrors *gr_rappi_line  = new TGraphAsymmErrors(5, rappi_mub, rappi_t);
    gr_rappi_line->SetLineWidth(3);
    gr_rappi_line->SetLineColor(kMagenta+2);


    //--------------------------------------
    // Coarse Graining T. Galatyuk et al. EPJA
    //--------------------------------------
    Double_t CGs_mub[] = {2.1, 2.42,   3, 6};
    Double_t CGs_t[]   = {43,    84, 130, 164.5};
    TGraphAsymmErrors *gr_CGs  = new TGraphAsymmErrors(4, CGs_mub, CGs_t);
    gr_CGs->SetPointError(0, 0, 0, 43*0.04, 43*0.04);
    gr_CGs->SetPointError(1, 0, 0, 84*0.04, 84*0.04);
    gr_CGs->SetPointError(2, 0, 0, 130*0.04, 130*0.04);
    gr_CGs->SetPointError(3, 0, 0, 164.5*0.04, 164.5*0.04);
    gr_CGs->SetMarkerColor(kPink-1);
    gr_CGs->SetLineColor(kPink-1);
    gr_CGs->SetLineWidth(1);
    gr_CGs->SetMarkerSize(1.8);
    gr_CGs->SetMarkerStyle(33);


    //--------------------------------------
    // T. Galatyuk et al. CG + R. Rapp& H.v. Hess
    //--------------------------------------
    TGraphAsymmErrors *gr_rapps_CGs_line  = new TGraphAsymmErrors(10);
    gr_rapps_CGs_line->SetPoint(0,2.1,43);
    gr_rapps_CGs_line->SetPoint(1,2.405050648,82.8170576);
    gr_rapps_CGs_line->SetPoint(2,2.692431027,109.5286178);
    gr_rapps_CGs_line->SetPoint(3,2.98905433,128.2267099);
    gr_rapps_CGs_line->SetPoint(4,3.50368801,142.7272711);
    gr_rapps_CGs_line->SetPoint(5,4.124132537,151.1223329);
    gr_rapps_CGs_line->SetPoint(6,4.95698546,158.7542072);
    gr_rapps_CGs_line->SetPoint(7,7.529645578,167.149269);
    gr_rapps_CGs_line->SetPoint(8,20.19522951,190.044892);
    gr_rapps_CGs_line->SetPoint(9,74.42284839,223.2435453);
    gr_rapps_CGs_line->SetPoint(10,198.7764717,255.6790112);
    gr_rapps_CGs_line->SetLineColor(kPink-1);
    gr_rapps_CGs_line->SetLineWidth(3);
    gr_rapps_CGs_line->SetLineStyle(9);


    //--------------------------------------
    // NA60+ 24 April 2018
    //--------------------------------------
    Double_t na60p_mub[] = {6.3, 8.8, 17.3};
    Double_t na60p_t[]   = {159, 166, 181};
    TGraphAsymmErrors *gr_na60p  = new TGraphAsymmErrors(3, na60p_mub, na60p_t);
    gr_na60p->SetPointError(0, 0, 0, 2, 2);
    gr_na60p->SetPointError(1, 0, 0, 3, 3);
    gr_na60p->SetPointError(2, 0, 0, 6, 6);
    gr_na60p->SetMarkerColor(kBlue+2);
    gr_na60p->SetLineColor(kBlue+2);
    gr_na60p->SetLineWidth(2);
    gr_na60p->SetMarkerSize(1.4);
    gr_na60p->SetMarkerStyle(22);


    //--------------------------------------
    // CBM April 2018
    //--------------------------------------
    Double_t cbm_mub[] = {3.3,  3.8, 4.3, 5};
    Double_t cbm_t[]   = {136, 145, 154, 159};
    TGraphAsymmErrors *gr_cbm  = new TGraphAsymmErrors(4, cbm_mub, cbm_t);
    gr_cbm->SetPointError(0, 0., 0., 1.77, 1.77);
    gr_cbm->SetPointError(1, 0., 0., 1.89, 1.89);
    gr_cbm->SetPointError(2, 0., 0., 2.00, 2.00);
    gr_cbm->SetPointError(3, 0., 0., 2.07, 2.07);
    gr_cbm->SetMarkerColor(kAzure);
    gr_cbm->SetLineColor(kAzure);
    gr_cbm->SetLineWidth(2);
    gr_cbm->SetMarkerSize(1.3);
    gr_cbm->SetMarkerStyle(20);







    //--------------------------------------
    //--------------------------------------
    //--------------------------------------
    TCanvas* can_qcd_cc = new TCanvas ("can__qcd_cc", "", 1020, 765);
    can_qcd_cc->SetFillColor(10);
    can_qcd_cc->SetBottomMargin(0.15);
    can_qcd_cc->SetTopMargin(0.04);
    can_qcd_cc->SetGridx();
    can_qcd_cc->SetGridy();
    can_qcd_cc->SetLogx();

    gPad->SetLeftMargin(0.11);
    gPad->SetRightMargin(0.025);

    gPad->SetTicks(1,1);

    h1->GetXaxis()->SetRangeUser(1,300);
    h1->GetYaxis()->SetRangeUser(0,275);

    h1->Draw();
    h1->GetXaxis()->SetNoExponent();
    h1->GetXaxis()->SetMoreLogLabels();

    gr_rappi->Draw("pesame");
    gr_rapps->Draw("psame");
    gr_CGs->Draw("psame");
    gr_rappi_line->Draw("lsame");
    gr_rapps_CGs_line->Draw("lsame");

    gr_na60->Draw("psame");
    gr_hades->Draw("plsame");


    TLatex *tex = new TLatex(18,215,"NA60");
    tex->SetTextSize(0.05);
    tex->SetTextFont(62);
    tex->SetLineWidth(2);
    tex->Draw();
    TLatex *tex = new TLatex(30.37,225.181,"T=205#pm12MeV");
    tex->SetTextSize(0.025);
    tex->SetTextFont(62);
    tex->SetLineWidth(2);
    tex->Draw();

    TLatex *tex = new TLatex(2.67,68,"HADES");
    tex->SetTextSize(0.05);
    tex->SetTextFont(62);
    tex->SetLineWidth(2);
    tex->Draw();
    TLatex *tex = new TLatex(5.7,77.25,"T=72#pm2MeV");
    tex->SetTextSize(0.025);
    tex->SetTextFont(62);
    tex->SetLineWidth(2);
    tex->Draw();

    TLatex *tex = new TLatex(22,250,"T_{initial}");
    tex->SetTextColor(kMagenta+2);
    tex->SetTextSize(0.05);

    tex->SetTextFont(62);
    tex->SetTextAngle(35);
    tex->SetLineWidth(2);
    tex->Draw();

    TLatex *tex = new TLatex(127,255,"T_{slope}");
    tex->SetTextColor(kPink-1);
    tex->SetTextSize(0.05);
    tex->SetTextFont(62);
    tex->SetTextAngle(23.1986);
    tex->SetLineWidth(2);
    tex->Draw();


//    gr_cbm->Draw("psame");
//    gr_na60p->Draw("psame");

    TLegend *leg = new TLegend(0.624754,0.170501,0.71611,0.354533);
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(2);
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    leg->AddEntry(gr_rappi ,"Theory estimate for T_{initial}" ,"p");
    leg->AddEntry(gr_CGs   ,"Theory estimate for T_{slope}"   ,"p");
    leg->AddEntry(gr_cbm   ,"CBM simulation (FAIR SIS100)"    ,"pe1");
    leg->AddEntry(gr_na60p ,"NA60^{+} simulation (CERN SPS)"  ,"pe1");
//    leg->Draw("same");



}