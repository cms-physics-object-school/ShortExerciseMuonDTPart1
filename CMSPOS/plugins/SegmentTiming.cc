#include "SegmentTiming.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>

//
// constructors and destructor
//
SegmentTiming::SegmentTiming(const edm::ParameterSet& iConfig) 
{
  edm::ConsumesCollector collector(consumesCollector());
  cscSegmentToken_ = consumes<CSCSegmentCollection>(edm::InputTag("cscSegments"));
  dtSegmentToken_ = consumes<DTRecSegment4DCollection>(edm::InputTag("dt4DSegments"));
}


SegmentTiming::~SegmentTiming()
{
  if (hFile!=0) {
    hFile->Close();
    delete hFile;
  }
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
SegmentTiming::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // cout << endl << " Event: " << iEvent.id() << "  Orbit: " << iEvent.orbitNumber() << "  BX: " << iEvent.bunchCrossing() << endl;

  edm::Handle<CSCSegmentCollection> allSegmentsCSC;
  iEvent.getByToken(cscSegmentToken_, allSegmentsCSC);

  edm::Handle<DTRecSegment4DCollection> dtRecHits;
  iEvent.getByToken(dtSegmentToken_, dtRecHits);  
  
  nHitsPhi=0;
  nHitsZed=0;
  for(CSCSegmentCollection::const_iterator hiti = allSegmentsCSC->begin(); hiti != allSegmentsCSC->end(); hiti++) {
    if ( !hiti->isValid()) continue; 
    nHitsCSC = hiti->nRecHits();
    time= hiti->time();
    t->Fill();
  }

  nHitsCSC=0; // we're filling DT segments now
  for (DTRecSegment4DCollection::const_iterator hiti = dtRecHits->begin(); hiti!=dtRecHits->end();++hiti) {
    if ( !hiti->isValid()) continue; 

    if (hiti->hasPhi()) {
      nHitsPhi = hiti->phiSegment()->recHits().size();
      nHitsZed=0;
      time= hiti->phiSegment()->t0();
      if (time!=-999) t->Fill();
    }
    
    if (hiti->hasZed()) {
      nHitsZed = hiti->zSegment()->recHits().size();
      nHitsPhi=0;
      time= hiti->zSegment()->t0();
      if (time!=-999) t->Fill();
    }
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
SegmentTiming::beginJob()
{

   hFile = new TFile( "segments.root", "recreate" );
   hFile->cd();

   t = new TTree("Segments", "Segments");
   t->Branch("nHitsCSC", &nHitsCSC, "nHitsCSC/I");
   t->Branch("nHitsPhi", &nHitsPhi, "nHitsPhi/I");
   t->Branch("nHitsZed", &nHitsZed, "nHitsZed/I");
   t->Branch("time", &time, "time/D");
}

// ------------- write ntuple to file  ------------
void SegmentTiming::endJob() {

  hFile->cd();
  t->Write();
  hFile->Write();
  delete t;  
}


//define this as a plug-in
DEFINE_FWK_MODULE(SegmentTiming);
