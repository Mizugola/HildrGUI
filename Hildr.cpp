#include "Hildr.hpp"

namespace hg
{
    //Size
    Size::Size(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    //Position
    Position::Position(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    //Element
    Element::Element(std::string id)
    {
        this->id = id;
    }
    std::string Element::getID()
    {
        return id;
    }
    Container* Element::getParent()
    {
        return parent;
    }

    //GraphicalElement
    GraphicalElement::GraphicalElement(std::string id, Position position, Size size) : Element(id)
    {
        type = Type::GraphicalElement;
        this->position = position;
        this->size = size;
    }
    Size GraphicalElement::getSize()
    {
        return size;
    }
    void GraphicalElement::setSize(Size size)
    {
        this->size = size;
    }
    Position GraphicalElement::getPosition()
    {
        return position;
    }
    void GraphicalElement::setPosition(Position position)
    {
        this->position = position;
    }

    //Container
    Container::Container(std::string id, Position position, Size size) : GraphicalElement(id, position, size)
    {
        type = Type::Container;
    }
    void addChild(Element* child)
    {
        if (child->isParent(nullptr) || child->isParent(this)) {
            childs.push_back(child);
            if (child->isParent(nullptr)) {
                child->setParent(this);
            }
        }
        else {
            
        }
    }


    void StartApp()
    {
        std::vector<std::string> toRemove;
        while (Container::Containers.size() > 0) {
            for (auto it = Container::Containers.begin(); it != Container::Containers.end(); it++) {
                if (it->second != nullptr && !it->second->update()) {
                    toRemove.push_back(it->first);
                }
            }
            if (toRemove.size() > 0) {
                for (int i = 0; i < toRemove.size(); i++) {
                    delete Container::Containers[toRemove[i]];
                    Container::Containers.erase(toRemove[i]);
                }
                toRemove.clear();
            }
            
        }
    }
}
