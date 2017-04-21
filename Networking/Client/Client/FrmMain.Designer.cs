namespace Client
{
    partial class FrmMain
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmMain));
            this.TxtFeed = new System.Windows.Forms.TextBox();
            this.TxtMessage = new System.Windows.Forms.TextBox();
            this.TmrProcessMessages = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // TxtFeed
            // 
            this.TxtFeed.Location = new System.Drawing.Point(12, 12);
            this.TxtFeed.Multiline = true;
            this.TxtFeed.Name = "TxtFeed";
            this.TxtFeed.ReadOnly = true;
            this.TxtFeed.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.TxtFeed.Size = new System.Drawing.Size(360, 211);
            this.TxtFeed.TabIndex = 0;
            this.TxtFeed.TabStop = false;
            this.TxtFeed.TextChanged += new System.EventHandler(this.TxtFeed_TextChanged);
            // 
            // TxtMessage
            // 
            this.TxtMessage.Location = new System.Drawing.Point(12, 229);
            this.TxtMessage.MaxLength = 1024;
            this.TxtMessage.Name = "TxtMessage";
            this.TxtMessage.Size = new System.Drawing.Size(360, 20);
            this.TxtMessage.TabIndex = 0;
            this.TxtMessage.KeyDown += new System.Windows.Forms.KeyEventHandler(this.TxtMessage_KeyDown);
            // 
            // TmrProcessMessages
            // 
            this.TmrProcessMessages.Tick += new System.EventHandler(this.TmrProcessMessages_Tick);
            // 
            // FrmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(384, 260);
            this.Controls.Add(this.TxtMessage);
            this.Controls.Add(this.TxtFeed);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "FrmMain";
            this.Text = "Slap Chat";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FrmMain_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox TxtFeed;
        private System.Windows.Forms.TextBox TxtMessage;
        private System.Windows.Forms.Timer TmrProcessMessages;
    }
}

