/************************************************************

 LBase.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013-2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LBASE_H
#define __LUCE_LBASE_H

class LBase : public LSelfKill
{
public:
    LBase(lua_State*, const String& name = "(unnamed)", bool pure = true);
    static int lnew(lua_State*);
    ~LBase();

    virtual void selfKill() override;

    //==============================================================================
    int light(lua_State*);
    int unlight(lua_State*);

    //==============================================================================
    int readOnly(lua_State*);
    int writeOnly(lua_State*);
    
    const String getBaseName() const;
protected:    
    //==============================================================================
    HashMap<String, bool> registered;
    void set( const String& r, int lua_type = LUA_TFUNCTION, int pos = -1);
    void unset( const String& r );
    void put( const String& r );
    bool get( const String& r );

    // avoid this constructor, it's causing issues with some compilers
    //int callback(const String& k, int nb_ret = 0, const std::list<var>& args = {}) const;
    int callback(const String& k, int nb_ret = 0, const std::list<var>& args = std::list<var>()) const;
    bool push_callback(const String& k) const;
    bool hasCallback(const String&) const;

private:    
    //==============================================================================
    lua_State *L;

    //==============================================================================
    HashMap<String,int> cb;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LBase)
};

#endif // __LUCE_LBASE_H
