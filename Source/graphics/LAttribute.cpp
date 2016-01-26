/************************************************************

 LAttribute.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LAttribute_inh.h"

const char LAttribute::className[] = "LAttribute";
const Luna<LAttribute>::PropertyType LAttribute::properties[] = {
    {"range", &LAttribute::getRange, &LBase::readOnly},
    {0,0}
};
const Luna<LAttribute>::FunctionType LAttribute::methods[] = {
    method( LAttribute, getColour ),
    method( LAttribute, getFont ),
    method( LAttribute, getRange ),
    {0,0}
};

const Luna<LAttribute>::StaticType LAttribute::statics[] = {
    {0,0}
};

LAttribute::LAttribute(lua_State *L)
    : LBase(L, "LAttribute", true),
      Attribute()
      //Attribute( Range<int>(), Colours::black )
{
    // INVALID (almost)
}

LAttribute::LAttribute(lua_State *L, const Attribute& class_)
    : LBase(L, "LAttribute", true),
      Attribute( class_ )
{
}

LAttribute::~LAttribute() {}

int LAttribute::getRange(lua_State*) {
    return LUCE::luce_pushtable( Attribute::range );
}

/////// getters
int LAttribute::getColour (lua_State *L) {
    //return LUA::returnUserdata<LColour, Colour>( AttributedString::Attribute::getColour() );
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L, Attribute::colour) );
}

int LAttribute::getFont (lua_State *L) {
    //return LUA::returnUserdata<LFont, Font>( Attribute::font );
    return LUA::storeAndReturnUserdata<LFont>( new LFont(L, Attribute::font) );
}
