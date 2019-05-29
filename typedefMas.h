typedef int twoi[2];

twoi smb;
twoi sma;

typedef twoi tv[2];

tv sdf;
tv sdf1;

void tst11(twoi& tf) //со ссылкой и без эффект одинаковый, но лучше использовать ссылку
{
	tf[1] = 9;
}

void typedefMas()
{
	tst11(smb);
	sdf[0][0] = sdf1[0][0];
	smb[1] = sma[1];
}