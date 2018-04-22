#pragma once
#include <vector>
#include <array>

template<typename T>
class Octree {
private:
    std::vector<Octree> children;
    std::vector<T> data;
    
public:
    std::array<int, 3> origin;
    int size = 32;
    int level = 0;
    
    T get(int i, int j, int k) {
        if (level == 0) {
            int index = i * size * size + j * size + k;
            return data[index];
        }
        
        if (children.size() == 0) {
            return 0;
        }
        
        int index = getChildIndex(i, j, k);
        return children[index].get(i, j, k);
    }
    
    void set(int i, int j, int k, T v) {
        if (level == 0) {
            if (data.size() == 0) {
                data.resize(size * size * size);
            }
            
            int index = i * size * size + j * size + k;
            data[index] = v;
        }
        
        if (children.size() == 0) {
            makeChildren();
        }
        
        int index = getChildIndex(i, j, k);
        children[index].set(i, j, k, v);
    }
    
    int getChildIndex(std::array<int, 3> origin) {
        return getChildIndex(origin[0], origin[1], origin[2]);
    }
    
    int getChildIndex(int i, int j, int k) {
        i -= origin[0];
        j -= origin[1];
        k -= origin[2];
        int index = 0;
        int hs = size / 2;
        if (i > hs) {
            index += 4;
        }
        if (j > hs) {
            index += 2;
        }
        if (k > hs) {
            index += 1;
        }
        return index;
    }
    
    void makeChildren() {
        int hs = size / 2;
        
        int i = origin[0];
        int j = origin[1];
        int k = origin[2];
        children.push_back(new Octree(i, j + 0, k + 0, level - 1));
        children.push_back(new Octree(i, j + 0, k + hs, level - 1));
        children.push_back(new Octree(i, j + hs, k + 0, level - 1));
        children.push_back(new Octree(i, j + hs, k + hs, level - 1));
        
        children.push_back(new Octree(i + hs, j + 0, k + 0, level - 1));
        children.push_back(new Octree(i + hs, j + 0, k + hs, level - 1));
        children.push_back(new Octree(i + hs, j + hs, k + 0, level - 1));
        children.push_back(new Octree(i + hs, j + hs, k + hs, level - 1));
    }
    
    void makeChildren(Octree existing) {
        int hs = size / 2;
        
        int childIndex = getChildIndex(existing.origin[0], existing.origin[1], existing.origin[2]);
        
        int i = origin[0];
        int j = origin[1];
        int k = origin[2];
        
        children.push_back(childIndex == children.size() ? existing : new Octree(i, j + 0, k + 0, level - 1));
        children.push_back(childIndex == children.size() ? existing : new Octree(i, j + 0, k + hs, level - 1));
        children.push_back(childIndex == children.size() ? existing : new Octree(i, j + hs, k + 0, level - 1));
        children.push_back(childIndex == children.size() ? existing : new Octree(i, j + hs, k + hs, level - 1));
        
        children.push_back(childIndex == children.size() ? existing : new Octree(i + hs, j + 0, k + 0, level - 1));
        children.push_back(childIndex == children.size() ? existing : new Octree(i + hs, j + 0, k + hs, level - 1));
        children.push_back(childIndex == children.size() ? existing : new Octree(i + hs, j + hs, k + 0, level - 1));
        children.push_back(childIndex == children.size() ? existing : new Octree(i + hs, j + hs, k + hs, level - 1));
    }
    
    Octree(int i, int j, int k, int level) : level(level) {
        origin[0] = i;
        origin[1] = j;
        origin[2] = k;
    }
};

template<typename T>
class ResizableOctree {
private:
    Octree<T> data;
    void expandTree(bool expandI, bool expandJ, bool expandK) {
        int i = expandI ? data.origin[0] : data.origin[0] - data.size;
        int j = expandJ ? data.origin[1] : data.origin[1] - data.size;
        int k = expandK ? data.origin[2] : data.origin[2] - data.size;
        Octree<T> parent = new Octree<T>(i, j, k, data.level + 1);
        parent.makeChildren(data);
        data = parent;
    }
public:
    T get(int i, int j, int k) {
        if (i < data.origin[0] || j < data.origin[1] || k < data.origin[2] ||
            i >= data.origin[0] + data.size || j >= data.origin[1] + data.size || k >= data.origin[2] + data.size) {
            return 0;
        }
        return data.get(i, j, k);
    }
    
    void set(int i, int j, int k, T v) {
        if (i < data.origin[0] || j < data.origin[1] || k < data.origin[2] ||
            i >= data.origin[0] + data.size || j >= data.origin[1] + data.size || k >= data.origin[2] + data.size) {
            expandTree(i >= data.origin[0] + data.size, j >= data.origin[1] + data.size, k >= data.origin[2] + data.size);
        }
        set(i, j, k, v);
    }
};
