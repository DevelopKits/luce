--[[----------------------------------------------------------------------------

  LClass.lua

  Luce Internal

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

-- TODO: this is just... a mess -- should start over

local new = function(self, ...)
    local self = self or {}
    --local me = self.class.new(class, ...)
    --local me = self.class.new(...)
    local r, me = pcall(self.class.new, ...)
    if not(r) then
        local name = (getmetatable(self.class) or {__tostring=function()return"none"end}).__tostring()
        require"pl.pretty".dump( self )
        error("LClass::"..name.."::new: "..(me or""), 2)
    end
    self.__self = me.__self
    for k,v in next, me do
        if ( k == "methods" ) then
            for _,f in next, v do
                self[f] = me[f] -- better than the methods table
            end
        -- TODO: find a smart way to get values when dumping
        elseif ( k == "vars" ) then
            self["vars"] = v
        else
            self[k] = v
        end
    end
    self.__exists = function(k) return me.__exists(me,k) end
    return setmetatable(self, {
        __tostring = me.__tostring,
        __self = me.__self,
        __index = function(t,k)
            if(LDEBUG)then
                if not(me.__exists(me,k)) then 
                    print("WARNING: trying to call non existing key:", k, me.__self)
                end
            end
            return me.__index(me, k) 
        end,
        -- FIXME: if returned value is nil, we can't detect if it's a nil index or a nil value !
        --
        __newindex = function(t, k, v)
            if not(me.__exists(me,k)) then
                if(LDEBUG)then
                    --print("NEWINDEX: setting local", k, me.__self)
                    pcall(rawset,t,k,v)
                else
                    rawset(t,k,v)
                end
            else
                if(LDEBUG)then
                    --print("NEWINDEX: setting native", k, me.__self)
                    pcall(function()me[k] = v end)
                else
                    me[k] = v
                end
            end
            --[[
            if not ( me.__index(me,k)
                and not ( me.__index(me,k) ) then
                    rawset(t,k,v)
                end
            else
                me[k] = v
            end
            --]]
        end
    })
end

return setmetatable({}, {
    __call = function(self, c, ...)
        assert(c, "Missing base class")
        return setmetatable({}, {
            __call = function(_, ...) return new({class=c}, ...) end
        })
    end
})
