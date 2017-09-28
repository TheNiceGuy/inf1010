#include <iostream>

#include "GroupImage.h"

using namespace std;

GroupImage::GroupImage() {
    type_     = "";
    capacity_ = 0;
}

GroupImage::~GroupImage() {
}

GroupImage::GroupImage(const string& type, uint_t capacity) {
    type_     = type;
    capacity_ = capacity;
}

GroupImage::GroupImage(const GroupImage& group) {
    type_     = group.getType();
    capacity_ = group.getCapacity();

    /* copy the image pointers*/
    for(uint_t i = 0; i < getSize(); i++)
        images_.push_back(group.getImage(i));
}

void GroupImage::setType(const string& type) {
    type_ = type;
}

string GroupImage::getType() const {
    return type_;
}

Image* GroupImage::getImage(uint_t index) const {
    /* make sure the index is valid */
    if(index >= getSize())
        return NULL;

    return images_[index];
}

uint_t GroupImage::getSize() const {
    return images_.size();
}

uint_t GroupImage::getCapacity() const {
    return capacity_;
}

void GroupImage::addImage(Image& image) {
    /* make sure there's space available */
    if(getSize() >= getCapacity()) {
        cout << "The group is at its maximum capacity." << endl;
        return;
    }

    /* make sure the name isn't duplicated */
    for(uint_t i = 0; i < getSize(); i++) {
        if(images_[i]->getName() == image) {
            cout << "Error: image name already present in the group." << endl;
            return;
        }
    }

    /* add the pointer into the vector */
    images_.push_back(&image);
    cout << "The image \"" << image.getName()
         << "\" has been successfully added." << endl;
}

void GroupImage::removeImage(const string& name) {
    /* search for the name */
    for(uint i = 0; i < getSize(); i++) {
        if(images_[i]->getName() == name) {
            images_.erase(images_.begin() + i);

            cout << "The image \"" << name
                 << "\" has been successfully removed." << endl;
            return;
        }
    }

    cout << "Error: the image couldn't be found." << endl;
}

void GroupImage::printImages() const {
    /* print all the image names */
    for(uint_t i = 0; i < getSize(); i++)
        images_[i]->printImage();
}

void GroupImage::doubleWidth(uint_t index) {
    /* make sure the index is valid */
    if(index >= getSize()) {
        cout << "Error: the index is invalid." << endl;
        return;
    }

    /* double the width of the image */
    images_[index]->doubleWidth();
    cout << "The image width has been doubled." << endl;
}

void GroupImage::doubleHeight(uint_t index) {
    /* make sure the index is valid */
    if(index >= getSize()) {
        cout << "Error: the index is invalid." << endl;
        return;
    }

    /* double the height of the image */
    images_[index]->doubleHeight();
    cout << "The image height has been doubled." << endl;
}

GroupImage& GroupImage::operator+=(Image& i) {
    addImage(i);

    return (*this);
}

GroupImage& GroupImage::operator-=(const Image& i) {
    removeImage(i.getName());

    return (*this);
}

ostream& operator<<(ostream& o, const GroupImage& g) {
    /* generate the output */
    for(uint_t i = 0; i < g.getSize(); i++)
        o << *g.getImage(i) << endl;

    return o;
}
