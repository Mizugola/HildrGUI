#pragma once

#include <iostream>
#include <string>
#include <future>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>
#include <map>

#include <SFML/Graphics.hpp>

namespace hg
{
    class GraphicalElement;
    class Container;
    class Panel;

    namespace Type
    {
        enum ElementType
        {
            Element = 0x0,
            GraphicalElement = 0x1,
            Container = 0x2,
            Panel = 0x3,
            Widget = 0x4
        };
    }

    class AlreadyOwnedException : public std::exception
    {
        public:
            AlreadyOwnedException(std::string elementId);
            virtual const char* what() const throw();
    };

    class Size
    {
        public:
            Size(int width = 0, int height = 0);
            int width = 0;
            int height = 0;
    };

    class Position
    {
        public:
            Position(int x = 0, int y = 0);
            int x = 0;
            int y = 0;
    }

    class Element
    {
        private:
            std::string id;
            Container* parent = nullptr;
            Type type = Type::Element;
        public:
            Element(std::string id);
            virtual std::string getID();
            virtual Container* getParent();
    };

    class GraphicalElement : public Element
    {
        private:
            Size size;
            Position position;
        public:
            GraphicalElement(std:::string id, Position position = Position(), Size size = Size());
            virtual Size getSize();
            virtual void setSize(Size size);
            virtual Position getPosition();
            virtual void setPosition(Position position);
    };

    class Container : public GraphicalElement
    {
        private:
            std::map<std::string, Element*> childs;
        public:
            Container(std::string id, Position position = Position(), Size size = Size());
            virtual void addChild(Element* child);
            template <typename T>
            virtual void ElementType getChild(std::string id);
    };

    class Panel : public Container
    {
        public:
            Panel(std::string id, Position position = Position(), Size size = Size());
    };

    class Widget : public GraphicalElement
    {

    };

    class Window
    {
        private:
            std::string title;
            Panel root;
            bool update();
            void handleEvents();
            friend void StartApp();
        public:
            std::string getTitle();
            void setTitle(std::string title);
    };

    extern std::map<std::string, Window*> Containers;

    void StartApp();
}
