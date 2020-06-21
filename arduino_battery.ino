int indpin = A3;
int cappin = A4;
float val = 0.0;

unsigned long start_time;
int clt_ind = 1;

const int N = 130;
float VL[N];
float Vc[N];
//float current_i[N];
unsigned long t_vec[N];
float c = 0.0001;
float R;

float Vmax;
float Vmin;
int idx_max;
int idx_min;
float I_Vmax;
float I_Vmin;

void setup()
{
  Serial.begin(9600);
  pinMode(indpin, INPUT);
  pinMode(cappin, INPUT);
}

void loop() {

  val = analogRead(indpin)/1023.0*5.0;
 if (val > 1.0 && clt_ind == 1)
  {
    start_time = micros();
    for (int n = 0; n < N; n++)
    {
      t_vec[n] = micros() - start_time;
      VL[n] = analogRead(indpin)/1023.0*5.0;
      Vc[n] = analogRead(cappin)/1023.0*5.0;
      delayMicroseconds(50);
    }
    //Serial.println(total_time);
 


//    for (int n = 0; n < N; n++)
//    {
//      //voltage value mapping
//      VL[n] = fmap(VL[n], 0, 1023, 0.0, 5.0);
//      Vc[n] = fmap(Vc[n], 0, 1023, 0.0, 5.0);
//      Serial.println(Vc[n],4);
//    }


    //Finding the maximum voltage and index
    //Initialization of variables
    Vmax = 0.000;
    Vmin = 5.00;
    idx_max = 0;
    idx_min = 0;
    for (int n = 0; n < N; n++)
    {
      if (VL[n] > Vmax)
      {
        Vmax = VL[n];
        idx_max = n;
      }
    }

    //Finding the mimnum voltage after occurence of maximum voltage and the index
    for (int n = idx_max; n < N; n++)
    {
      if (VL[n] < Vmin)
      {
        Vmin = VL[n];
        idx_min = n;
      }
    }

    //Calculation of discretization of current and replace Vc[n] = i[n] for low memory
//    for (int n = 0; n < N; n++)
//    {
//      Vc[n] = c * ((Vc[n+1] - Vc[n]) / ((t_vec[n+1] - t_vec[n]) * 0.000001));
//      //current_i[n] = c * ((Vc[n] - Vc[n-1]) / 0.0004);
//      //Serial.println(t_vec[n]);
//      
//      Serial.println(Vc[n],4);
//    }
    // shift n for current. i,tmax[n+1] occurs at vmax[n]?
    // find the maximum and minium current
    // Vc is now having i, current data
    //I_Vmax = Vc[idx_max];
    //I_Vmin = Vc[idx_min];

    Serial.println("Time(us)   VL   Vc");
    Serial.println("-------------------------------------");

    for (int n = 0; n < N; n++)
    {
      Serial.print(t_vec[n]*0.001);
      Serial.print("\t");
      Serial.print(VL[n],4);
      Serial.print("\t");
      Serial.println(Vc[n],4);
  
    }
    
    
    I_Vmax  = c*((Vc[idx_max+1] - Vc[idx_max-1])/((t_vec[idx_max+1] - t_vec[idx_max-1]) * 0.000001));
    I_Vmin  = c*((Vc[idx_min+1] - Vc[idx_min-1])/((t_vec[idx_min+1] - t_vec[idx_min-1]) * 0.000001));
    //R = (Vmax - Vmin) / (I_Vmax - I_Vmin);
    R = (Vmin - Vmax) / (I_Vmax - I_Vmin);

    Serial.print("Vmax: ");
    Serial.println(Vmax,4);
    Serial.print("Vmin: ");
    Serial.println(Vmin,4);
    Serial.print("I,Vmax: ");
    Serial.println(I_Vmax,4);
    Serial.print("I,Vmin: ");
    Serial.println(I_Vmin,4);
    Serial.print("Resistance Estimated: ");
    Serial.println(R,4);

    clt_ind = 0;
  }

}

//float fmap(float x, float in_min, float in_max, float out_min, float out_max)
//{
//  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//}
