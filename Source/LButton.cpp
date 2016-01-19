/************************************************************

 LButton.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#include "LButton_inh.h"

const char LButton::className[] = "LButton";
const Luna<LButton>::PropertyType LButton::properties[] = {
    {0,0}
};
const Luna<LButton>::FunctionType LButton::methods[] = {
    {0,0}
};

LButton::LButton(lua_State *Ls, Button* child_, const String& name_)
    : child(child_),
      LComponent(Ls, child_, name_)
{
    L = Ls;
}

LButton::~LButton(){
    if(child)
        child.release();
}

/////// callbacks
void LButton::lpaintButton( Graphics& g,bool isMouseOverButton,bool isButtonDown ) {
    if (child && hasCallback("paintButton")) {
        callback("paintButton", 0, { 
            new LRefBase("Graphics", &g),
            isMouseOverButton, isButtonDown } );
    }
}
int LButton::paintButton(lua_State*){
    if (child)
        set("paintButton");
    return 0;
}

void LButton::lclicked( const ModifierKeys& modifiers ) {
    if (child && hasCallback("clicked"))
        callback("clicked");
}
int LButton::clicked(lua_State*){
    if (child)
        set("clicked");
    return 0;
}

void LButton::linternalClickCallback( const ModifierKeys& modifierKeys_ ) {
    if (child && hasCallback("internalClickCallback"))
        callback("internalClickCallback");
}
int LButton::internalClickCallback(lua_State*){
    if (child)
        set("internalClickCallback");
    return 0;
}

void LButton::ltriggerClick() {
    if (child && hasCallback("triggerClick"))
        callback("triggerClick");
}
int LButton::triggerClick(lua_State*){
    if (child)
        set("triggerClick");
    return 0;
}

void LButton::lbuttonStateChanged() {
    if (child && hasCallback("buttonStateChanged") )
        callback("buttonStateChanged");
}
int LButton::buttonStateChanged(lua_State*) {
    if (child)
        set("buttonStateChanged");
    return 0;
}

// Button::Listener
void LButton::lbuttonClicked(Button*) {
    if(child && hasCallback("buttonClicked"))
        callback("buttonClicked");
}
int LButton::buttonClicked(lua_State*) {
    if(child)
        set("buttonClicked");
    return 0;
}

/////// getters/setters
int LButton::getClickingTogglesState ( lua_State* ) {
    if (child) {
        return LUA::returnBoolean( child->getClickingTogglesState() );
    } else return 0;
}
int LButton::setClickingTogglesState ( lua_State* ) {
    if (child) {
        child->setClickingTogglesState(LUA::getBoolean());
    }
    return 0;
}

int LButton::getToggleState ( lua_State* ) {
    if (child) {
        return LUA::returnBoolean( child->getToggleState() );
    } else return 0;
}
int LButton::setToggleState ( lua_State* ) {
    bool shouldBeOn = LUA::getBoolean(2);
    // FIXME: notif should be optional
    int notif = LUA::getNumber<int>(2);
    if (child)
        child->setToggleState( shouldBeOn, (NotificationType)notif );
    return 0;
}

int LButton::getRadioGroupId ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getRadioGroupId() );
    else return 0;
}
int LButton::setRadioGroupId ( lua_State* ) {
    int newGroupId = LUA::getNumber<int>(2);
    int notif = LUA::getNumber<int>(2);
    if (child)
        child->setRadioGroupId( newGroupId, (NotificationType)notif );
    return 0;
}

int LButton::getTooltip ( lua_State* ) {
    if (child)
        return LUA::returnString( child->getTooltip() );
    else return 0;
}
int LButton::setTooltip ( lua_State* ) {
    if (child)
        child->setTooltip(LUA::checkAndGetString());
    return 0;
}

int LButton::getButtonText ( lua_State* ) {
    if (child)
        return LUA::returnString( child->getButtonText() );
    else return 0;
}
int LButton::setButtonText ( lua_State* ) {
    if (child)
        child->setButtonText(LUA::getString());
    return 0;
}

/////// getters
int LButton::getConnectedEdgeFlags ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getConnectedEdgeFlags() );
    else return 0;
}

int LButton::isConnectedOnRight ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isConnectedOnRight() );
    else return 0;
}

int LButton::isConnectedOnTop ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isConnectedOnTop() );
    else return 0;
}

int LButton::isOver ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isOver() );
    else return 0;
}

int LButton::isDown ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isDown() );
    else return 0;
}

int LButton::isConnectedOnLeft ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isConnectedOnLeft() );
    else return 0;
}

int LButton::isConnectedOnBottom ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isConnectedOnBottom() );
    else return 0;
}

int LButton::getMillisecondsSinceButtonDown ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getMillisecondsSinceButtonDown() );
    else return 0;
}

/////// setters
int LButton::setConnectedEdges ( lua_State* ) {
    if (child)
        child->setConnectedEdges(LUA::getNumber());
    return 0;
}

int LButton::clearShortcuts ( lua_State* ) {
    if (child)
        child->clearShortcuts();
    return 0;
}

int LButton::setTriggeredOnMouseDown ( lua_State* ) {
    if (child)
        child->setTriggeredOnMouseDown(LUA::getBoolean());
    return 0;
}

int LButton::setRepeatSpeed ( lua_State* ) {
    int initialDelayInMillisecs = LUA::getNumber();
    int repeatDelayInMillisecs = LUA::getNumber();
    int minimumDelayInMillisecs = LUA::checkAndGetNumber(2, -1);
    if (child)
        child->setRepeatSpeed( initialDelayInMillisecs, repeatDelayInMillisecs, minimumDelayInMillisecs );
    return 0;
}

int LButton::addShortcut ( lua_State *L ) {
    if (child)
        child->addShortcut( *LUA::from_luce<LKeyPress>(2) );
    return 0;
}

int LButton::setState ( lua_State* ) {
    if (child)
        child->setState( (Button::ButtonState)LUA::getNumber<int>(2) );
    return 0;
}

int LButton::isRegisteredForShortcut ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isRegisteredForShortcut( *LUA::from_luce<LKeyPress>(2) ) );
    return 0;
}

// TODO
// getters
int LButton::getCommandID ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_CommandID( child->getCommandID() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "CommandID getCommandID()" );
    } else return 0;
}

// could make a callback instead of using Value
int LButton::getToggleStateValue ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_Value( child->getToggleStateValue() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Value getToggleStateValue()" );
    } else return 0;
}

int LButton::setCommandToTrigger ( lua_State* ) {
    if (child) {
        // ApplicationCommandManager* commandManagerToUse = LUA::TODO_OBJECT_ApplicationCommandManager;
        // CommandID commandID = LUA::TODO_OBJECT_CommandID;
        bool generateTooltip = LUA::getBoolean(4);
        // child->setCommandToTrigger( commandManagerToUse, commandID, generateTooltip );
        LUA::TODO_OBJECT( "setCommandToTrigger,  commandManagerToUse, commandID, generateTooltip " );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}
