movs r0, #0
movs r1, #1
movs r2, #170
movs r3, #255
movs r4, #15

rsbs r4, r4, #0
@r4 value should be -15, FFFFFFF1
@flags N=1, Z=0, C=0, V=0

asrs r4, r4, #1
@r4 value should be -8, FFFFFFF8
@flags N=1, Z=0, C=1, V=0

movs r5, #5
@flags N=0, Z=0, C=1, V=0
adcs r5, r1
@r5 value should be 7, 7
@flags N=0, Z=0, C=0, V=0

sbcs r5, r1
@r5 decimal value should be 5, 5
@flags N=0, Z=0, C=1, V=0
sbcs r5, r1
@r5 decimal value should be 4, 4
@flags N=0, Z=0, C=1, V=0

movs r6, #170
rors r6, r1
@r5 value should be 85, 55

tst r2, r6
@flag Z should be activated, flags value should be 0100

@Needs shift_add_sub_move to be implemented
