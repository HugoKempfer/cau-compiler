class Foo {
  int property_a = -12;

  String bar() {
    if (true == false) {
      return "HI";
    }
    if (2 < -3) {
      print("Impossible")
    }
    return "HI";
  }

  bool loop_func(int nb_iter) {
    int it = 0;
    while (it < nb_iter) {
      it = it + 1;
    }
    return false;
  }
}
