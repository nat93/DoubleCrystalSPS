#include "EventAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

EventAction::EventAction(RunAction* runAct) : runAction(runAct)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* event)
{
    G4int eventID = event->GetEventID();

    if(eventID%100 == 0)
    {
        printf("\r--> BeginOfEvent: %12d",eventID);
        fflush(stdout);
    }
}

void EventAction::EndOfEventAction(const G4Event*)
{
    runAction->tree_1->Fill();
}
