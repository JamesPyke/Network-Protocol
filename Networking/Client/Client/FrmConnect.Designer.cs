namespace Client
{
    partial class FrmConnect
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if(disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmConnect));
            this.NmuPort = new System.Windows.Forms.NumericUpDown();
            this.TxtHostname = new System.Windows.Forms.TextBox();
            this.LblIP = new System.Windows.Forms.Label();
            this.LblPort = new System.Windows.Forms.Label();
            this.BtnConnect = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.NmuPort)).BeginInit();
            this.SuspendLayout();
            // 
            // NmuPort
            // 
            this.NmuPort.Location = new System.Drawing.Point(216, 6);
            this.NmuPort.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.NmuPort.Name = "NmuPort";
            this.NmuPort.Size = new System.Drawing.Size(50, 20);
            this.NmuPort.TabIndex = 1;
            this.NmuPort.Value = new decimal(new int[] {
            1234,
            0,
            0,
            0});
            // 
            // TxtHostname
            // 
            this.TxtHostname.Location = new System.Drawing.Point(34, 6);
            this.TxtHostname.MaxLength = 39;
            this.TxtHostname.Name = "TxtHostname";
            this.TxtHostname.Size = new System.Drawing.Size(141, 20);
            this.TxtHostname.TabIndex = 0;
            this.TxtHostname.Text = "127.0.0.1";
            // 
            // LblIP
            // 
            this.LblIP.AutoSize = true;
            this.LblIP.Location = new System.Drawing.Point(8, 9);
            this.LblIP.Name = "LblIP";
            this.LblIP.Size = new System.Drawing.Size(20, 13);
            this.LblIP.TabIndex = 0;
            this.LblIP.Text = "IP:";
            // 
            // LblPort
            // 
            this.LblPort.AutoSize = true;
            this.LblPort.Location = new System.Drawing.Point(181, 9);
            this.LblPort.Name = "LblPort";
            this.LblPort.Size = new System.Drawing.Size(29, 13);
            this.LblPort.TabIndex = 0;
            this.LblPort.Text = "Port:";
            // 
            // BtnConnect
            // 
            this.BtnConnect.Location = new System.Drawing.Point(11, 32);
            this.BtnConnect.Name = "BtnConnect";
            this.BtnConnect.Size = new System.Drawing.Size(255, 23);
            this.BtnConnect.TabIndex = 2;
            this.BtnConnect.Text = "Connect";
            this.BtnConnect.UseVisualStyleBackColor = true;
            this.BtnConnect.Click += new System.EventHandler(this.BtnConnect_Click);
            // 
            // FrmConnect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(279, 62);
            this.Controls.Add(this.BtnConnect);
            this.Controls.Add(this.LblPort);
            this.Controls.Add(this.LblIP);
            this.Controls.Add(this.TxtHostname);
            this.Controls.Add(this.NmuPort);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "FrmConnect";
            this.Text = "Connect";
            ((System.ComponentModel.ISupportInitialize)(this.NmuPort)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown NmuPort;
        private System.Windows.Forms.TextBox TxtHostname;
        private System.Windows.Forms.Label LblIP;
        private System.Windows.Forms.Label LblPort;
        private System.Windows.Forms.Button BtnConnect;
    }
}