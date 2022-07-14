package android.hardware.invcase;

@VintfStability
interface IInvcase {
    String getChars();
    void putChars(in String msg);
}