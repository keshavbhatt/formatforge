#ifndef CACHE_H
#define CACHE_H

class Cache {
public:
  static Cache &instance();

private:
  Cache();

  // delete copy constructor and assignment operator to prevent copying
  Cache(const Cache &) = delete;
  Cache &operator=(const Cache &) = delete;
};

#endif // CACHE_H
