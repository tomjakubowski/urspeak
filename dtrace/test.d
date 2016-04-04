/* -*- mode: dtrace-script; -*- */

urspeak*:::respire_start {
  begin_us = timestamp / 1000;
  printf("started!\n");
}

urspeak*:::respire_done {
  done_us = timestamp / 1000;
  printf("spent %d usecs bellowing children.\n", done_us - begin_us);
}
