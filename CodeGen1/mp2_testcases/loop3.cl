class Main {
  main(): Int {
    let i: Int <- 0 in {
      while i < 10 loop {
        i <- i + 1;
      } pool;
      i;
    }
  };
};
