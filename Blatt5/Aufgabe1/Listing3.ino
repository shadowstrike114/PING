int h( int z, int e) {
  int zquadrat = z*z;
  int ergebnis = zquadrat;
  for (int i = 1; i < e;i++)
    ergebnis *= zquadrat;
  return ergebnis;
}
