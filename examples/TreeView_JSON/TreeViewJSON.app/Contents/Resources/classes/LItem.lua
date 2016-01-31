--[[
LUCE TreeViewItem item object

(c) 2014, Peersuasive Technologies
--]]

local luce = _G.Luce
local className = "LItem"

local function new(self, id, val, istop, dblClick, changeOpenness)
    local comp  = luce:MainComponent("container")
    local field = luce:Label(id or "<root>")
    field.text = (id or "<root>") .. ( val and " "..val or "")
    field:setMinimumHorizontalScale( 1.0 );
    field:setJustificationType( luce.JustificationType.centredLeft );
    comp:addAndMakeVisible( field )
    comp:addMouseListener(true)
    comp:resized(function(...)
        field:setSize{ comp:getWidth(), comp:getHeight() }
    end)

    comp:mouseDoubleClick(function(mouseEvent)
        if ( mouseEvent.mods:isLeftButtonDown() ) then
            dblClick( mouseEvent )
        else
            changeOpenness()
        end
    end)

    --comp:mouseWheelMove(function(mouseEvent, mouseWheelDetails)
    --    print("mouse wheel")
    --end)
    return comp
end

return setmetatable({}, {
    __call = new,
    __tostring = function() return className end,
})
