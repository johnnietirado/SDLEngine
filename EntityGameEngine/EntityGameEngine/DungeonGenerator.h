#pragma once
#include <SDL.h>
#include <vector>
#include "TextureManager.h"
#include <algorithm>
#include <time.h>
#include <iostream>
#include <string>
#include <random>
#include <cassert>
#include <cstdio>

class Leaf
{
public:
	int x, y, width, height;
	Leaf(){}
	~Leaf(){}
	Leaf* leftChild;
	Leaf* rightChild;
	SDL_Rect* room;
	std::vector<SDL_Rect> hallways;

	Leaf(int X, int Y, int Width, int Height)
	{
		x = X;
		y = Y;
		width = Width;
		height = Height;
		leftChild = NULL;
		rightChild = NULL;
		room = NULL;
	}
	
	bool split()
	{
		
		if (leftChild != NULL || rightChild != NULL)
			return false;

		bool splitH = (rand() % 100) > 50;
		if (width > height && height / width >= 0.05)
			splitH = false;
		else if (height > width && width / height >= 0.05)
			splitH = true;

		int max = (splitH ? height : width) - MIN_LEAF_SIZE;
		if (max <= MIN_LEAF_SIZE)
			return false;

		int split = (rand() % (max - MIN_LEAF_SIZE)) + MIN_LEAF_SIZE;
		if (splitH)
		{
			leftChild = new Leaf(x, y, width, split);
			rightChild = new Leaf(x, y + split, width, height - split);
		}
		else
		{
			leftChild = new Leaf(x, y, split, height);
			rightChild = new Leaf(x + split, y, width - split, height);
		}
		return true;
	}

	void createRooms()
	{
		if (leftChild != NULL || rightChild != NULL)
		{
			if (leftChild != NULL)
				leftChild->createRooms();

			if (rightChild != NULL)
				rightChild->createRooms();

			if (rightChild != NULL && leftChild != NULL)
				createHall(leftChild->getRoom(), rightChild->getRoom());
		}
		else
		{
			Vector2D roomSize, roomPos;
			int x1, y1;
			int rrr = rand();
			x1 = (rand() % (width-50)) + 45;
			y1 = (rand() % (height-50)) + 45;
			roomSize = Vector2D(x1, y1);

			x1 = (rand() % (width - (int)roomSize.getX())) + 1;
			y1 = (rand() % (height - (int)roomSize.getY())) + 1;
			roomPos = Vector2D(x1, y1);
			room = new SDL_Rect();
			room->x = x + roomPos.getX();
			room->y = y + roomPos.getY();
			room->w = roomSize.getX();
			room->h = roomSize.getY();
		}
	}

	SDL_Rect* getRoom()
	{
		if (room != NULL)
			return room;
		else
		{
			SDL_Rect* lRoom;
			SDL_Rect* rRoom;
			if (leftChild != NULL)
			{
				lRoom = leftChild->getRoom();
			}
			if (rightChild != NULL)
			{
				rRoom = rightChild->getRoom();
			}

			if (lRoom == NULL && rRoom == NULL)
				return NULL;
			else if (rRoom == NULL)
				return lRoom;
			else if (lRoom == NULL)
				return rRoom;
			else if (rand() % 100 > 50)
				return lRoom;
			else
				return rRoom;
		}
	}

	void createHall(SDL_Rect* l, SDL_Rect* r)
	{
		int x1, y1;

		x1 = (rand() % ((l->x + l->w - 10) - l->x)) + (l->x);
		y1 = (rand() % ((l->y + l->h - 10) - l->y)) + (l->y);
		Vector2D p1 = Vector2D(x1, y1);

		x1 = (rand() % ((r->x + r->w - 10) - r->x)) + (r->x);
		y1 = (rand() % ((r->y + r->h - 10) - r->y)) + (r->y);
		Vector2D p2 = Vector2D(x1, y1);

		int w = p2.getX() - p1.getX();
		int h = p2.getY() - p1.getY();

		if (w < 0)
		{
			if (h < 0)
			{
				if (rand() % 100 > 50)
				{
					SDL_Rect r1 = { p2.getX(), p1.getY(), abs(w), 10 };
					hallways.push_back(r1);
					SDL_Rect r2 = { p2.getX(), p2.getY(), 10, abs(h) };
					hallways.push_back(r2);
				}
				else
				{
					SDL_Rect r1 = { p2.getX(), p2.getY(), abs(w), 10 };
					hallways.push_back(r1);
					SDL_Rect r2 = { p1.getX(), p2.getY(), 10, abs(h) };
					hallways.push_back(r2);
				}
			}
			else if (h > 0)
			{
				if (rand() % 100 > 50)
				{
					SDL_Rect r1 = { p2.getX(), p1.getY(), abs(w), 10 };
					hallways.push_back(r1);
					SDL_Rect r2 = { p2.getX(), p1.getY(), 10, abs(h) };
					hallways.push_back(r2);
				}
				else
				{
					SDL_Rect r1 = { p2.getX(), p2.getY(), abs(w), 10 };
					hallways.push_back(r1);
					SDL_Rect r2 = { p1.getX(), p1.getY(), 10, abs(h) };
					hallways.push_back(r2);
				}
			}
			else
			{
				SDL_Rect r1 = { p2.getX(), p2.getY(), abs(w), 10 };
				hallways.push_back(r1);
			}
		}
		else if (w > 0)
		{
			if (h < 0)
			{
				if (rand() % 100 > 50)
				{
					SDL_Rect r1 = { p1.getX(), p2.getY(), abs(w), 10 };
					hallways.push_back(r1);
					SDL_Rect r2 = { p1.getX(), p2.getY(), 10, abs(h) };
					hallways.push_back(r2);
				}
				else
				{
					SDL_Rect r1 = { p1.getX(), p1.getY(), abs(w), 10 };
					hallways.push_back(r1);
					SDL_Rect r2 = { p2.getX(), p2.getY(), 10, abs(h) };
					hallways.push_back(r2);
				}
			}

			else if (h > 0)
			{
				if (rand() % 100 > 50)
				{
					SDL_Rect r1 = { p1.getX(), p1.getY(), abs(w), 10 };
					hallways.push_back(r1);
					SDL_Rect r2 = { p2.getX(), p1.getY(), 10, abs(h) };
					hallways.push_back(r2);
				}
				else
				{
					SDL_Rect r1 = { p1.getX(), p2.getY(), abs(w), 10 };
					hallways.push_back(r1);
					SDL_Rect r2 = { p1.getX(), p1.getY(), 10, abs(h) };
					hallways.push_back(r2);
				}
			}
			else
			{
				SDL_Rect r1 = { p1.getX(), p1.getY(), abs(w), 10 };
				hallways.push_back(r1);
			}
		}
		else
		{
			if (h < 0)
			{
				SDL_Rect r2 = { p2.getX(), p2.getY(), 10, abs(h) };
				hallways.push_back(r2);
			}
			else if (h > 0)
			{
				SDL_Rect r1 = { p1.getX(), p1.getY(), 10, abs(h) };
				hallways.push_back(r1);
			}
		}
	}
	
private:
	const unsigned int MIN_LEAF_SIZE = 120;
};

class MapCreator
{
public:
	MapCreator(){ srand(time(NULL)); }
	~MapCreator(){}

	void Generate()
	{
		Leaf* root = new Leaf(0, 0, 640, 480);
		leafs.push_back(root);
		int i = 0;

		bool didSplit = true;
		while (didSplit)
		{
			didSplit = false;
			for (i = 0; i < leafs.size(); ++i)
			{
				if (leafs[i]->leftChild == NULL && leafs[i]->rightChild == NULL)
				{
					if (leafs[i]->width > MAX_LEAF_SIZE || leafs[i]->height > MAX_LEAF_SIZE || (rand() % 100) > 75)
					{
						if (leafs[i]->split())
						{
							leafs.push_back(leafs[i]->leftChild);
							leafs.push_back(leafs[i]->rightChild);
							didSplit = true;
						}
					}
				}
			}
		}
		root->createRooms();
		for (i = 0; i < leafs.size(); ++i)
		{
			if (leafs[i]->getRoom() != NULL)
			{
				rooms.push_back(leafs[i]->getRoom());
			}
		}
	}
	
	std::vector<Leaf*> getLeafs() { return leafs; }
	std::vector<SDL_Rect*> getRooms() { return rooms; }
private:
	const unsigned int MAX_LEAF_SIZE = 128;
	std::vector<Leaf*> leafs;
	std::vector<SDL_Rect*> rooms;
};