#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
  MyPrimaryGenerator *primaryGenerator = new MyPrimaryGenerator();
  SetUserAction(primaryGenerator);

  MyRunAction *runAction = new MyRunAction();  // Saves the root file
  SetUserAction(runAction);
}
