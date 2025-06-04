import { Component, Input } from '@angular/core';
import { ReactiveFormsModule } from '@angular/forms';

type InputTypes = "text" | "email" | "password"

@Component({
  selector: 'app-primary-input',
  imports: [
    ReactiveFormsModule
  ],
  templateUrl: './primary-input.html',
  styleUrl: './primary-input.scss'
})
export class PrimaryInput {
  @Input() type: InputTypes = "text";
  @Input() formName: string = "";
  @Input() placeholder: string= "";
  @Input() label: string= "";

}
